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
	{
		mlx_destroy_all(mlx_data);
		return (1);
	}
	mlx_data->img.img_ptr = mlx_new_image(mlx_data->mlx_ptr, WIDTH, HEIGHT);
	if (mlx_data->img.img_ptr == NULL)
	{
		mlx_destroy_all(mlx_data);
		return (1);
	}
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
		free_scene(&data->scene);
		mlx_destroy_all(&data->mlx);
		exit(0);
	}

	// If we have a selected object, handle transforms
	if (data->selected_object)
	{
		const t_object *obj = data->selected_object;
		int changed = 0;

		// Translation with WASDQE and arrow keys
		if (keycode == KeyA || keycode == KeyLeft) { // -X
			if (obj->type == SPHERE) ((t_sphere*)obj)->center.x -= MOVE_STEP;
			else if (obj->type == PLANE) ((t_plane*)obj)->point.x -= MOVE_STEP;
			else if (obj->type == CYLINDER) ((t_cylinder*)obj)->center.x -= MOVE_STEP;
			changed = 1;
		}
		else if (keycode == KeyD || keycode == KeyRight) { // +X
			if (obj->type == SPHERE) ((t_sphere*)obj)->center.x += MOVE_STEP;
			else if (obj->type == PLANE) ((t_plane*)obj)->point.x += MOVE_STEP;
			else if (obj->type == CYLINDER) ((t_cylinder*)obj)->center.x += MOVE_STEP;
			changed = 1;
		}
		else if (keycode == KeyQ) { // +Y (up)
			if (obj->type == SPHERE) ((t_sphere*)obj)->center.y += MOVE_STEP;
			else if (obj->type == PLANE) ((t_plane*)obj)->point.y += MOVE_STEP;
			else if (obj->type == CYLINDER) ((t_cylinder*)obj)->center.y += MOVE_STEP;
			changed = 1;
		}
		else if (keycode == KeyE) { // -Y (down)
			if (obj->type == SPHERE) ((t_sphere*)obj)->center.y -= MOVE_STEP;
			else if (obj->type == PLANE) ((t_plane*)obj)->point.y -= MOVE_STEP;
			else if (obj->type == CYLINDER) ((t_cylinder*)obj)->center.y -= MOVE_STEP;
			changed = 1;
		}
		else if (keycode == KeyW || keycode == KeyUp) { // +Z (forward)
			if (obj->type == SPHERE) ((t_sphere*)obj)->center.z += MOVE_STEP;
			else if (obj->type == PLANE) ((t_plane*)obj)->point.z += MOVE_STEP;
			else if (obj->type == CYLINDER) ((t_cylinder*)obj)->center.z += MOVE_STEP;
			changed = 1;
		}
		else if (keycode == KeyS || keycode == KeyDown) { // -Z (back)
			if (obj->type == SPHERE) ((t_sphere*)obj)->center.z -= MOVE_STEP;
			else if (obj->type == PLANE) ((t_plane*)obj)->point.z -= MOVE_STEP;
			else if (obj->type == CYLINDER) ((t_cylinder*)obj)->center.z -= MOVE_STEP;
			changed = 1;
		}

		// Rotation helpers (Euler small-angle)
		if (!changed && (keycode == KeyI || keycode == KeyK || keycode == KeyJ || keycode == KeyL || keycode == KeyU || keycode == KeyO))
		{
			double rx = 0.0, ry = 0.0, rz = 0.0;
			double step = ROTATE_STEP_DEG * M_PI / 180.0;
			if (keycode == KeyI) rx += step; // +X
			if (keycode == KeyK) rx -= step; // -X
			if (keycode == KeyJ) ry += step; // +Y
			if (keycode == KeyL) ry -= step; // -Y
			if (keycode == KeyU) rz += step; // +Z
			if (keycode == KeyO) rz -= step; // -Z

			if (obj->type == PLANE)
			{
				t_plane *pl = (t_plane*)obj;
				t_vector3 v = pl->normal;
				// Rz * Ry * Rx
				// Rx
				t_vector3 t;
				double cx = cos(rx), sx = sin(rx);
				double cy = cos(ry), sy = sin(ry);
				double cz = cos(rz), sz = sin(rz);
				t.x = v.x;
				t.y = v.y * cx - v.z * sx;
				t.z = v.y * sx + v.z * cx;
				// Ry
				v.x = t.x * cy + t.z * sy;
				v.y = t.y;
				v.z = -t.x * sy + t.z * cy;
				// Rz
				t.x = v.x * cz - v.y * sz;
				t.y = v.x * sz + v.y * cz;
				t.z = v.z;
				pl->normal = t;
				if (vector3_normalize_safe(pl->normal, &pl->normal_unit, 1e-12) == 0)
					pl->normal_unit = VECTOR3_UNIT_Y;
				changed = 1;
			}
			else if (obj->type == CYLINDER)
			{
				t_cylinder *cyl = (t_cylinder*)obj;
				t_vector3 v = cyl->orientation;
				t_vector3 t;
				double cx = cos(rx), sx = sin(rx);
				double cy = cos(ry), sy = sin(ry);
				double cz = cos(rz), sz = sin(rz);
				// Rx
				t.x = v.x;
				t.y = v.y * cx - v.z * sx;
				t.z = v.y * sx + v.z * cx;
				// Ry
				v.x = t.x * cy + t.z * sy;
				v.y = t.y;
				v.z = -t.x * sy + t.z * cy;
				// Rz
				t.x = v.x * cz - v.y * sz;
				t.y = v.x * sz + v.y * cz;
				t.z = v.z;
				cyl->orientation = t;
				if (vector3_normalize_safe(cyl->orientation, &cyl->axis_unit, 1e-12) == 0)
					cyl->axis_unit = VECTOR3_UNIT_Y;
				changed = 1;
			}
		}

		// Scaling: PageUp/PageDown for diameter; Home/End could be added for height; here use PageUp/PageDown and keep height on cylinder via Q/E? We'll keep separate keys below
		if (!changed && (keycode == KeyPageUp || keycode == KeyPageDown))
		{
			double k = (keycode == KeyPageUp) ? SCALE_STEP : (1.0 / SCALE_STEP);
			if (obj->type == SPHERE)
			{
				t_sphere *sp = (t_sphere*)obj;
				double d = sp->diameter * k;
				if (d > 1e-6) { sp->diameter = d; changed = 1; }
			}
			else if (obj->type == CYLINDER)
			{
				t_cylinder *cyl = (t_cylinder*)obj;
				double d = cyl->diameter * k;
				if (d > 1e-6) { cyl->diameter = d; changed = 1; }
			}
		}
		// Height scaling for cylinder with Shifted PageUp/PageDown not available here; map to Up/Down already used. Use Left/Right? To avoid conflicts, map to J/L with Ctrl ideally. Keep simple: map to W/S with Page modifiers skipped. Use additional keys: ']' increase height, '[' decrease height.
		if (!changed && (keycode == 93 /*]*/ || keycode == 91 /*[*/))
		{
			if (obj->type == CYLINDER)
			{
				t_cylinder *cyl = (t_cylinder*)obj;
				double k = (keycode == 93) ? SCALE_STEP : (1.0 / SCALE_STEP);
				double h = cyl->height * k;
				if (h > 1e-6) { cyl->height = h; changed = 1; }
			}
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
