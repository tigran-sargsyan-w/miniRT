/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:47:46 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/02 16:54:18 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "constants.h"

// 3D vector structure
typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}			t_vector3;

// predefined vectors
t_vector3	vector3_zero(void);
t_vector3	vector3_one(void);
t_vector3	vector3_unit_x(void);
t_vector3	vector3_unit_y(void);
t_vector3	vector3_unit_z(void);

// vector creation and checking
t_vector3	vector3_create(double x, double y, double z);
int			vector3_is_finite(t_vector3 v);
int			vector3_equal_eps(t_vector3 a, t_vector3 b, double eps);
int			vector3_is_zero_eps(t_vector3 v, double eps);

// Arithmetic (scalar)
t_vector3	vector3_add(t_vector3 a, t_vector3 b);
t_vector3	vector3_subtract(t_vector3 a, t_vector3 b);
t_vector3	vector3_negate(t_vector3 v);
t_vector3	vector3_scale(t_vector3 v, double k);
t_vector3	vector3_divide_scalar(t_vector3 v, double k);
t_vector3	vector3_add_scaled(t_vector3 a, t_vector3 b, double k);

// Arithmetic component-wise
t_vector3	vector3_multiply_componentwise(t_vector3 a, t_vector3 b);
t_vector3	vector3_divide_componentwise(t_vector3 a, t_vector3 b);
int			vector3_divide_componentwise_safe(t_vector3 a, t_vector3 b,
				double eps, t_vector3 *out);

// Norms / normalization
double		vector3_length_squared(t_vector3 v);
double		vector3_length(t_vector3 v);
int			vector3_normalize_safe(t_vector3 v, t_vector3 *out, double eps);

// Dot product / Cross product
double		vector3_dot(t_vector3 a, t_vector3 b);
t_vector3	vector3_cross(t_vector3 a, t_vector3 b);

// Utilities
t_vector3	vector3_abs(t_vector3 v);
t_vector3	vector3_min(t_vector3 a, t_vector3 b);
t_vector3	vector3_max(t_vector3 a, t_vector3 b);
t_vector3	vector3_clamp(t_vector3 v, double mn, double mx);
t_vector3	vector3_lerp(t_vector3 a, t_vector3 b, double t);

#endif
