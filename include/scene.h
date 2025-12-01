/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:28 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 22:42:45 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ambient.h"
# include "camera.h"
# include "color.h"
# include "cylinder.h"
# include "light.h"
# include "plane.h"
# include "sphere.h"

typedef struct s_scene
{
	int			has_ambient;
	t_ambient	ambient;
	int			has_camera;
	t_camera	camera;
	int			has_light;
	t_light		light;
	t_sphere	*spheres;
	int			sphere_count;
	t_plane		*planes;
	int			plane_count;
	t_cylinder	*cylinders;
	int			cylinder_count;
}				t_scene;

#endif
