/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:47:16 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/14 22:47:16 by dsemenov         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vector vec_create(float x, float y, float z)
{
    return (t_vector){x, y, z};
}

t_vector vec_add(t_vector a, t_vector b)
{
    return (t_vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vector vec_sub(t_vector a, t_vector b)
{
    return (t_vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vector vec_scale(t_vector v, float s)
{
    return (t_vector){v.x * s, v.y * s, v.z * s};
}

float vec_dot(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float vec_length(t_vector v)
{
    return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector vec_normalize(t_vector v)
{
    float length;
    
    length = vec_length(v);
    if (length == 0)
        return (t_vector){0, 0, 0};
    return vec_scale(v, 1.0f / length);
}

