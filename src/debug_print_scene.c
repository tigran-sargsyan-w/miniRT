#include "scene.h"
#include <stdio.h>

void	debug_print_scene(t_scene *scene)
{
	t_sphere	*sp;

	printf("Scene Debug Info:\n");
	printf("Ambient Light: %d\n", scene->has_ambient);
    if (scene->has_ambient)
    {
        printf(" Intensity: %.2f Color: (%d, %d, %d)\n",
            scene->ambient.intensity,
            scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
    }
    printf("Camera: %d\n", scene->has_camera);
    if (scene->has_camera)
    {
        printf(" Position: (%.2f, %.2f, %.2f) Orientation: (%.2f, %.2f, %.2f) FOV: %d\n",
            scene->camera.position.x, scene->camera.position.y, scene->camera.position.z,
            scene->camera.orientation.x, scene->camera.orientation.y, scene->camera.orientation.z,
            scene->camera.fov);
    }
    printf("Light: %d\n", scene->has_light);
    if (scene->has_light)
    {
        printf("Position: (%.2f, %.2f, %.2f) Color: (%d, %d, %d) Intensity: %.2f\n",
            scene->light.position.x, scene->light.position.y, scene->light.position.z,
            scene->light.color.r, scene->light.color.g, scene->light.color.b,
            scene->light.intensity);
    }
	printf("Number of Spheres: %d\n", scene->sphere_count);
    for (int i = 0; i < scene->sphere_count; ++i)
    {
        sp = &scene->spheres[i];
        printf(" Sphere %d: Center(%.2f, %.2f, %.2f), Diameter: %.2f, Color(%d, %d, %d)\n", i,
            sp->center.x, sp->center.y, sp->center.z,
            sp->diameter, sp->color.r, sp->color.g, sp->color.b);
    }
    printf("Number of Planes: %d\n", scene->plane_count);
    for (int i = 0; i < scene->plane_count; ++i)
    {
        t_plane *pl = &scene->planes[i];
        printf(" Plane %d: Point(%.2f, %.2f, %.2f), Normal(%.2f, %.2f, %.2f),  Color(%d, %d, %d)\n", i,
            pl->point.x, pl->point.y, pl->point.z,
            pl->normal.x, pl->normal.y, pl->normal.z,
            pl->color.r, pl->color.g, pl->color.b);
    }
    printf("Number of Cylinders: %d\n", scene->cylinder_count);
    for (int i = 0; i < scene->cylinder_count; ++i)
    {
        t_cylinder *cy = &scene->cylinders[i];
        printf(" Cylinder %d: Center(%.2f, %.2f, %.2f), Orientation(%.2f, %.2f, %.2f), Diameter: %.2f, Height: %.2f, Color(%d, %d, %d)\n", i,
            cy->center.x, cy->center.y, cy->center.z,
            cy->orientation.x, cy->orientation.y, cy->orientation.z,
            cy->diameter, cy->height,
            cy->color.r, cy->color.g, cy->color.b);
    }
}