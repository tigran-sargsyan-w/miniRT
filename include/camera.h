#ifndef CAMERA_H
# define CAMERA_H
# include "ray.h"
# include "vector.h"

typedef struct s_camera
{
	t_vector3	position;
	t_vector3	forward;
	t_vector3	right;
	t_vector3	up;
	double		half_width;
	double		half_height;
}				t_camera;

int				camera_init(t_camera *camera, t_vector3 position,
					t_vector3 look_dir, double fov_deg, int img_width,
					int img_height);
t_ray			camera_ray(const t_camera *camera, int pixel_x, int pixel_y,
					int img_width, int img_height);

#endif
