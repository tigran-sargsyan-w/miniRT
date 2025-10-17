/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:47:16 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/17 18:21:40 by tsargsya         ###   ########.fr       */
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

/* additional utilities */
t_vector vec_mul(t_vector a, t_vector b)
{
    return (t_vector){a.x * b.x, a.y * b.y, a.z * b.z};
}

t_vector vec_div_s(t_vector v, float s)
{
    if (s == 0.0f)
        return (t_vector){0, 0, 0};
    return vec_scale(v, 1.0f / s);
}

float vec_len2(t_vector v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector vec_cross(t_vector a, t_vector b)
{
    return (t_vector){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

int vec_near_zero(t_vector v)
{
    const float s = 1e-8f;
    return (fabsf(v.x) < s && fabsf(v.y) < s && fabsf(v.z) < s);
}

t_vector vec_reflect(t_vector v, t_vector n)
{
    // reflect v around normal n: v - 2*dot(v,n)*n
    float d = vec_dot(v, n);
    return vec_sub(v, vec_scale(n, 2.0f * d));
}

/* math helpers */
float deg2rad(float deg)
{
    return (deg * (M_PI / 180.0f));
}

/* robust quadratic solver: returns number of real roots (0,1,2).
   Uses numerically stable formulation to reduce catastrophic cancellation. */
int solve_quadratic(float a, float b, float c, float roots[2])
{
    if (a == 0.0f)
    {
        if (b == 0.0f)
            return 0;
        // linear solution bx + c = 0
        if (roots)
            roots[0] = -c / b;
        return 1;
    }
    float disc = b * b - 4.0f * a * c;
    if (disc < 0.0f)
        return 0;
    float sqrt_disc = sqrtf(disc);
    // use numerically stable form
    float q = -0.5f * (b + (b >= 0.0f ? sqrt_disc : -sqrt_disc));
    float r1 = q / a;
    float r2 = c / q;
    if (disc == 0.0f)
    {
        if (roots)
            roots[0] = r1;
        return 1;
    }
    if (roots)
    {
        if (r1 < r2)
        {
            roots[0] = r1;
            roots[1] = r2;
        }
        else
        {
            roots[0] = r2;
            roots[1] = r1;
        }
    }
    return 2;
}

