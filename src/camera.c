#include <math.h>
#include "camera.h"
#include "vector.h"
#include "constants.h"

int	camera_init(t_camera *camera, t_vector3 position,
				 t_vector3 look_dir, double fov_deg, int img_width,
				 int img_height)
{
	t_vector3	forward;
	t_vector3	right;
	t_vector3	world_up;
	double		fov_rad;
	double		aspect;

	if (!camera || img_width <= 0 || img_height <= 0)
		return (1);
	if (!isfinite(fov_deg) || fov_deg <= 0.0 || fov_deg >= 180.0)
		return (1);
	if (!vector3_is_finite(look_dir)
		|| !vector3_normalize_safe(look_dir, &forward, RT_EPS))
		return (1);

	camera->position = position;
	camera->forward = forward;

	/* выбрать world_up; если близко к оси Y, переключиться на X */
	world_up = VECTOR3_UNIT_Y;
	if (fabs(vector3_dot(forward, world_up)) > 0.999)
		world_up = VECTOR3_UNIT_X;

	right = vector3_cross(world_up, forward);
	if (!vector3_normalize_safe(right, &right, RT_EPS))
		return (1);

	camera->right = right;
	camera->up = vector3_cross(forward, right);

	/* Горизонтальный FOV */
	fov_rad = fov_deg * (M_PI / 180.0);
	camera->half_width = tan(fov_rad * 0.5);

	aspect = (double)img_width / (double)img_height;
	if (!isfinite(aspect) || aspect <= 0.0)
		return (1);
	camera->half_height = camera->half_width / aspect;

	return (0);
}

t_ray	camera_ray(const t_camera *camera, int pixel_x, int pixel_y,
				 int img_width, int img_height)
{
	double		u; /* NDC x in [-1,1] Normalized Device Coordinates */
	double		v; /* NDC y in [-1,1] Normalized Device Coordinates */
	double		x;
	double		y;
	t_vector3	dir;
	t_vector3	ndir;

	u = ((double)pixel_x + 0.5) / (double)img_width * 2.0 - 1.0;
	v = 1.0 - ((double)pixel_y + 0.5) / (double)img_height * 2.0;

	x = u * camera->half_width;
	y = v * camera->half_height;

	/* dir = forward + right*x + up*y */
	dir = vector3_add(camera->forward, vector3_scale(camera->right, x));
	dir = vector3_add(dir,            vector3_scale(camera->up,    y));

	if (!vector3_normalize_safe(dir, &ndir, RT_EPS))
		ndir = camera->forward;

	return (ray_make(camera->position, ndir));
}
