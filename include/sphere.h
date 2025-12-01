/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:32 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 22:42:48 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "color.h"
# include "material.h"
# include "object.h"
# include "vector.h"

typedef struct s_sphere
{
	t_object	base;
	t_vector3	center;
	t_color8	color;
	double		diameter;
}				t_sphere;

int				sphere_init(t_sphere *sphere, t_vector3 center, double diameter,
					t_material material);

#endif
