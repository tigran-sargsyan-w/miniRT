/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:52:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/07 00:20:42 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <stdio.h>

/**
 * @brief Prints main scene components (ambient, camera, light)
 * Handy for quick console debug of scene header info
 * @param s - scene to inspect
 */
void	print_scene_objects(t_scene *s)
{
	if (s->has_ambient)
		printf("Ambient Light: %d\n Inten: %.2f Col: (%d, %d, %d)\n",
			s->has_ambient, s->ambient.intensity,
			s->ambient.color.r, s->ambient.color.g, s->ambient.color.b);
	if (s->has_camera)
		printf("Camera: %d\n Pos: (%.2f, %.2f, %.2f) Ori: (%.2f, %.2f, %.2f)"
			" FOV: %d\n", s->has_camera,
			s->camera.position.x, s->camera.position.y, s->camera.position.z,
			s->camera.orientation.x, s->camera.orientation.y,
			s->camera.orientation.z, s->camera.fov);
	if (s->has_light)
		printf("Light: %d\n Pos: (%.2f, %.2f, %.2f) Col: (%d, %d, %d)"
			" Inten: %.2f\n", s->has_light,
			s->light.position.x, s->light.position.y, s->light.position.z,
			s->light.color.r, s->light.color.g, s->light.color.b,
			s->light.intensity);
}

/**
 * @brief Prints all spheres in scene with basic properties
 * @param scene - scene containing spheres array
 */
void	print_spheres(t_scene *scene)
{
	int			i;
	t_sphere	*sp;

	i = 0;
	printf("Number of Spheres: %d\n", scene->sphere_count);
	while (i < scene->sphere_count)
	{
		sp = &scene->spheres[i];
		printf(" Sphere %d: Center(%.2f, %.2f, %.2f),"
			" Diameter: %.2f, Color(%d, %d, %d)\n",
			i,
			sp->center.x, sp->center.y, sp->center.z,
			sp->diameter,
			sp->color.r, sp->color.g, sp->color.b);
		i++;
	}
}

/**
 * @brief Prints all planes in scene with position and normal
 * @param scene - scene containing planes array
 */
void	print_planes(t_scene *scene)
{
	int			i;
	t_plane		*pl;

	i = 0;
	printf("Number of Planes: %d\n", scene->plane_count);
	while (i < scene->plane_count)
	{
		pl = &scene->planes[i];
		printf(" Plane %d: Point(%.2f, %.2f, %.2f),"
			" Normal(%.2f, %.2f, %.2f), Color(%d, %d, %d)\n",
			i,
			pl->point.x, pl->point.y, pl->point.z,
			pl->normal.x, pl->normal.y, pl->normal.z,
			pl->color.r, pl->color.g, pl->color.b);
		i++;
	}
}

/**
 * @brief Prints all cylinders in scene with transform and color
 * @param scene - scene containing cylinders array
 */
void	print_cylinders(t_scene *scene)
{
	int			i;
	t_cylinder	*cy;

	i = 0;
	printf("Number of Cylinders: %d\n", scene->cylinder_count);
	while (i < scene->cylinder_count)
	{
		cy = &scene->cylinders[i];
		printf(" Cylinder %d: Center(%.2f, %.2f, %.2f),"
			" Orientation(%.2f, %.2f, %.2f),"
			" Diameter: %.2f, Height: %.2f, Color(%d, %d, %d)\n",
			i,
			cy->center.x, cy->center.y, cy->center.z,
			cy->orientation.x, cy->orientation.y, cy->orientation.z,
			cy->diameter, cy->height,
			cy->color.r, cy->color.g, cy->color.b);
		i++;
	}
}

/**
 * @brief High-level helper to dump entire scene to stdout
 * Calls individual print_* functions for each object type
 * @param scene - scene to debug print
 */
void	debug_print_scene(t_scene *scene)
{
	printf("Scene Debug Info:\n");
	print_scene_objects(scene);
	print_spheres(scene);
	print_planes(scene);
	print_cylinders(scene);
}
