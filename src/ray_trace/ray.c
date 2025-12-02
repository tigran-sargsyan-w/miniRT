/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:05:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 21:07:51 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

/**
 * @brief Creates a ray from origin and direction
 * @param orig - ray origin point
 * @param dir - ray direction (should be normalized)
 * @return t_ray - new ray
 */
t_ray	ray_make(t_vector3 orig, t_vector3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = dir;
	return (ray);
}

/**
 * @brief Computes point along ray at given distance
 * P(t) = origin + t * direction
 * @param ray - ray to trace along
 * @param distance - parameter t (distance along ray)
 * @return t_vector3 - point on ray at distance t
 */
t_vector3	ray_at(const t_ray *ray, double distance)
{
	return (vector3_add(ray->orig, vector3_scale(ray->dir, distance)));
}
