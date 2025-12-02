/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:47:10 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/02 23:40:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "hit.h"
# include "ray.h"
# include "vector.h"

typedef struct s_object			t_object;
typedef struct s_object_node	t_object_node;

typedef int						(*t_intersect_func)(const t_object *object,
									t_ray ray, double t_min, double t_max,
									t_hit *hit_result);
typedef void					(*t_translate_func)(t_object *object,
									t_vector3 delta);
typedef void					(*t_rotate_euler_func)(t_object *object,
									double rx, double ry, double rz);
typedef void					(*t_scale_func)(t_object *object,
									double factor);
typedef void					(*t_scale_height_func)(t_object *object,
									double factor);

typedef struct s_object_funcs
{
	t_intersect_func		intersect;
	t_translate_func		translate;
	t_rotate_euler_func		rotate_euler;
	t_scale_func			scale_uniform;
	t_scale_height_func		scale_height;
}	t_object_funcs;

typedef enum e_object_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	COMMENT
}	t_object_type;

struct						s_object
{
	t_object_type			type;
	t_material				material;
	t_intersect_func		intersect_func;
	t_translate_func		translate;
	t_rotate_euler_func		rotate_euler;
	t_scale_func			scale_uniform;
	t_scale_height_func		scale_height;
};

struct						s_object_node
{
	const t_object			*object;
	struct s_object_node	*next;
};

void						object_init(t_object *object, t_object_type type,
								t_material material, t_object_funcs funcs);

#endif
