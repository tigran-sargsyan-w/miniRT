/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:47:16 by dsemenov          #+#    #+#             */
/*   Updated: 2025/10/17 20:31:02 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vector3 vector3_create(double x, double y, double z)
{
    return (t_vector3){x, y, z};
}

t_vector3 vector3_add(t_vector3 a, t_vector3 b)
{
    return (t_vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vector3 vector3_sub(t_vector3 a, t_vector3 b)
{
    return (t_vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vector3 vector3_scale(t_vector3 v, double s)
{
    return (t_vector3){v.x * s, v.y * s, v.z * s};
}

double vector3_dot(t_vector3 a, t_vector3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double vector3_length(t_vector3 v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector3 vector3_normalize(t_vector3 v)
{
    double length;
    
    length = vector3_length(v);
    if (length == 0)
        return (t_vector3){0, 0, 0};
    return vector3_scale(v, 1.0 / length);
}

/* additional utilities */
t_vector3 vector3_mul(t_vector3 a, t_vector3 b)
{
    return (t_vector3){a.x * b.x, a.y * b.y, a.z * b.z};
}

t_vector3 vector3_div_s(t_vector3 v, double s)
{
    if (s == 0.0)
        return (t_vector3){0, 0, 0};
    return vector3_scale(v, 1.0 / s);
}

double vector3_len2(t_vector3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector3 vector3_cross(t_vector3 a, t_vector3 b)
{
    return (t_vector3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

int vector3_near_zero(t_vector3 v)
{
    const double s = 1e-12;
    return (fabs(v.x) < s && fabs(v.y) < s && fabs(v.z) < s);
}

t_vector3 vector3_reflect(t_vector3 v, t_vector3 n)
{
    // reflect v around normal n: v - 2*dot(v,n)*n
    double d = vector3_dot(v, n);
    return vector3_sub(v, vector3_scale(n, 2.0 * d));
}

/* math helpers */
double deg2rad(double deg)
{
    return (deg * (M_PI / 180.0));
}

/* robust quadratic solver: returns number of real roots (0,1,2).
   Uses numerically stable formulation to reduce catastrophic cancellation. */
int solve_quadratic(double a, double b, double c, double roots[2])
{
    if (a == 0.0)
    {
        if (b == 0.0)
            return 0;
        // linear solution bx + c = 0
        if (roots)
            roots[0] = -c / b;
        return 1;
    }
    double disc = b * b - 4.0 * a * c;
    if (disc < 0.0)
        return 0;
    double sqrt_disc = sqrt(disc);
    // use numerically stable form
    double q = -0.5 * (b + (b >= 0.0 ? sqrt_disc : -sqrt_disc));
    double r1 = q / a;
    double r2 = c / q;
    if (disc == 0.0)
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

