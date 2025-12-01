/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:23 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 22:42:42 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vector.h"

typedef struct s_ray
{
	t_vector3	orig;
	t_vector3	dir;
}				t_ray;

t_ray			ray_make(t_vector3 orig, t_vector3 dir);
t_vector3		ray_at(const t_ray *ray, double distance);

#endif
