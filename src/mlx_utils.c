#include "libft.h"
#include "mlx_utils.h"
#include "miniRT.h"
#include "ray.h"
#include "hit.h"
#include "camera.h"
#include "constants.h"
#include "trace.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"
#include "vector.h"
#include <math.h>
#include <mlx.h>
#include <stdlib.h>

void	mlx_destroy_all(t_mlx_data *mlx_data)
{
	if (mlx_data->img.img_ptr)
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img.img_ptr);
	if (mlx_data->win_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	if (mlx_data->mlx_ptr)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

int	mlx_init_system(t_mlx_data *mlx_data, char *name)
{
	ft_bzero(mlx_data, sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	if (mlx_data->mlx_ptr == NULL)
		return (1);
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WIDTH, HEIGHT, name);
	if (mlx_data->win_ptr == NULL)
		return (1);
	mlx_data->img.img_ptr = mlx_new_image(mlx_data->mlx_ptr, WIDTH, HEIGHT);
	if (mlx_data->img.img_ptr == NULL)
		return (1);
	mlx_data->img.pixels_ptr = mlx_get_data_addr(mlx_data->img.img_ptr,
			&mlx_data->img.bits_per_pixel, &mlx_data->img.line_length,
			&mlx_data->img.endian);
	return (0);
}

void	my_mlx_pixel_put(t_img_data *image_data, int x, int y, int color)
{
	char	*dst;

	dst = image_data->pixels_ptr + (y * image_data->line_length + x
			* (image_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	on_keypress(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == KeyEscape)
	{
		if (data->selected_object)
		{
			data->selected_object = NULL;
			if (render_scene(data) == 0)
				mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
			return (0);
		}
			free_scene(&data->scene);
			if (data->ray_dir_cache) 
			{ 
				free(data->ray_dir_cache);
				data->ray_dir_cache = NULL; 
			}
			free(data->objbuf);
			mlx_destroy_all(&data->mlx);
		exit(0);
	}

	// If we have a selected object, handle transforms via object hooks
	if (data->selected_object)
	{
		const t_object *obj = data->selected_object;
		int changed = 0;
		// Translation with WASDQE and arrow keys
		if (obj->translate) {
			t_vector3 d = VECTOR3_ZERO;
			if (keycode == KeyA || keycode == KeyLeft) d.x -= MOVE_STEP;
			else if (keycode == KeyD || keycode == KeyRight) d.x += MOVE_STEP;
			else if (keycode == KeyQ) d.y += MOVE_STEP;
			else if (keycode == KeyE) d.y -= MOVE_STEP;
			else if (keycode == KeyW || keycode == KeyUp) d.z += MOVE_STEP;
			else if (keycode == KeyS || keycode == KeyDown) d.z -= MOVE_STEP;
			if (d.x != 0.0 || d.y != 0.0 || d.z != 0.0) {
				obj->translate((t_object*)obj, d);
				changed = 1;
			}
		}

		// Rotation helpers (Euler small-angle)
		if (!changed && obj->rotate_euler && (keycode == KeyI || keycode == KeyK || keycode == KeyJ || keycode == KeyL || keycode == KeyU || keycode == KeyO))
		{
			double rx = 0.0, ry = 0.0, rz = 0.0;
			double step = ROTATE_STEP_DEG * M_PI / 180.0;
			if (keycode == KeyI) rx += step; // +X
			if (keycode == KeyK) rx -= step; // -X
			if (keycode == KeyJ) ry += step; // +Y
			if (keycode == KeyL) ry -= step; // -Y
			if (keycode == KeyU) rz += step; // +Z
			if (keycode == KeyO) rz -= step; // -Z
			if (rx != 0.0 || ry != 0.0 || rz != 0.0) {
				obj->rotate_euler((t_object*)obj, rx, ry, rz);
				changed = 1;
			}
		}

		// Uniform scaling via PageUp/PageDown
		if (!changed && obj->scale_uniform && (keycode == KeyPageUp || keycode == KeyPageDown))
		{
			double k = (keycode == KeyPageUp) ? SCALE_STEP : (1.0 / SCALE_STEP);
			obj->scale_uniform((t_object*)obj, k);
			changed = 1;
		}
		// Height scaling for shapes that support it: '[' decrease, ']' increase
		if (!changed && obj->scale_height && (keycode == 93 /*]*/ || keycode == 91 /*[*/))
		{
			double k = (keycode == 93) ? SCALE_STEP : (1.0 / SCALE_STEP);
			obj->scale_height((t_object*)obj, k);
			changed = 1;
		}

		if (changed)
		{
			if (render_scene(data) == 0)
				mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
		}
	}
	return (0);
}

static int	on_destroy(void *param)
{
	t_data *data;

	data = (t_data *)param;
	free_scene(&data->scene);
	if (data->ray_dir_cache) 
	{ 
		free(data->ray_dir_cache);
		data->ray_dir_cache = NULL;
	}
	free(data->objbuf);
	mlx_destroy_all(&data->mlx);
	exit(0);
	return (0);
}

static int on_mouse(int button, int x, int y, void *param)
{
	t_data *data;
	t_hit hit;

	(void)button; // We only handle left click (1), but ignore other buttons silently
	data = (t_data *)param;
	if (!data || !data->scene.has_camera)
		return (0);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (0);

	if (button == 1)
	{
		t_ray ray = camera_ray(&data->scene.camera, x, y, WIDTH, HEIGHT);
		if (scene_intersect(&data->scene, ray, K_TMIN_PRIMARY, K_TMAX_PRIMARY, &hit))
			data->selected_object = hit.object;
		else
			data->selected_object = NULL;
		if (render_scene(data) == 0)
			mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
	}
	return (0);
}

void	install_event_handlers(t_data *data)
{
	if (!data || !data->mlx.win_ptr)
		return ;
	mlx_key_hook(data->mlx.win_ptr, &on_keypress, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, &on_destroy, data);
	mlx_mouse_hook(data->mlx.win_ptr, &on_mouse, data);
}
