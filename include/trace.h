/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:47:39 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 23:47:39 by dsemenov         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
#define TRACE_H

#include "scene.h"
#include "ray.h"
#include "hit.h"

int scene_intersect(const t_scene *scene, t_ray ray, double t_min, double t_max, t_hit *out_hit);

// Fast boolean occlusion query for shadow rays
int scene_occluded(const t_scene *scene, t_ray ray, double t_min, double t_max);

#endif
