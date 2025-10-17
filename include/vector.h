#ifndef VECTOR_H
# define VECTOR_H

# define M_PI 3.14159265358979323846
# define RT_EPS 1e-9

// 3D vector structure
typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}			t_vector3;

// predefined vectors
# define VECTOR3_ZERO ((t_vector3){0.0, 0.0, 0.0})
# define VECTOR3_ONE ((t_vector3){1.0, 1.0, 1.0})
# define VECTOR3_UNIT_X ((t_vector3){1.0, 0.0, 0.0})
# define VECTOR3_UNIT_Y ((t_vector3){0.0, 1.0, 0.0})
# define VECTOR3_UNIT_Z ((t_vector3){0.0, 0.0, 1.0})

// vector creation and checking
t_vector3	vector3_create(double x, double y, double z);
int			vector3_is_finite(t_vector3 v);
int			vector3_equal_eps(t_vector3 a, t_vector3 b, double eps);
int			vector3_is_zero_eps(t_vector3 v, double eps);

// Arithmetic (scalar)
t_vector3	vector3_add(t_vector3 a, t_vector3 b); // (a + b)
t_vector3	vector3_subtract(t_vector3 a, t_vector3 b); // (a - b)
t_vector3	vector3_negate(t_vector3 v); // (-v)
t_vector3	vector3_scale(t_vector3 v, double k); // (v * k)
t_vector3	vector3_divide_scalar(t_vector3 v, double k); // (v / k)
t_vector3	vector3_add_scaled(t_vector3 a, t_vector3 b, double k); // (a + k*b) (удобно для ray_at: O + t*D)

// Arithmetic component-wise
t_vector3	vector3_multiply_componentwise(t_vector3 a, t_vector3 b); // (a ⊙ b) (useful for colors)
t_vector3	vector3_divide_componentwise(t_vector3 a, t_vector3 b);   // (a ⊘ b)
int			vector3_divide_componentwise_safe(t_vector3 a, t_vector3 b, double eps, t_vector3 *out); // safe component-wise division

// Norms / normalization
double		vector3_length_squared(t_vector3 v); // |v|^2
double		vector3_length(t_vector3 v); // |v|
int			vector3_normalize_safe(t_vector3 v, t_vector3 *out, double eps); // safe normalization v/|v|

// Dot product / Cross product
double		vector3_dot(t_vector3 a, t_vector3 b); // a · b (углы/Ламберт)
t_vector3	vector3_cross(t_vector3 a, t_vector3 b); // a × b (перпендикуляр/базисы)

// Utilities
t_vector3	vector3_abs(t_vector3 v);
t_vector3	vector3_min(t_vector3 a, t_vector3 b);          // покомпонентный min
t_vector3	vector3_max(t_vector3 a, t_vector3 b);          // покомпонентный max
t_vector3	vector3_clamp(t_vector3 v, double mn, double mx); // Ограничение компоненты интервалом
t_vector3	vector3_lerp(t_vector3 a, t_vector3 b, double t); // линейная интерполяция (a*(1-t) + b*t)

#endif