#include <math.h>
#include "vector.h"

/* === vector creation and checking === */

t_vector3	vector3_create(double x, double y, double z)
{
	t_vector3 v = { x, y, z };
	return v;
}

int	vector3_is_finite(t_vector3 v)
{
	return (isfinite(v.x) != 0) && (isfinite(v.y) != 0) && (isfinite(v.z) != 0);
}

int	vector3_equal_eps(t_vector3 a, t_vector3 b, double eps)
{
	if (fabs(a.x - b.x) > eps) return 0;
	if (fabs(a.y - b.y) > eps) return 0;
	if (fabs(a.z - b.z) > eps) return 0;
	return 1;
}

int	vector3_is_zero_eps(t_vector3 v, double eps)
{
	return (fabs(v.x) <= eps) && (fabs(v.y) <= eps) && (fabs(v.z) <= eps);
}

/* === Arithmetic (scalar) === */

t_vector3	vector3_add(t_vector3 a, t_vector3 b)
{
	return (t_vector3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

t_vector3	vector3_subtract(t_vector3 a, t_vector3 b)
{
	return (t_vector3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

t_vector3	vector3_negate(t_vector3 v)
{
	return (t_vector3){ -v.x, -v.y, -v.z };
}

t_vector3	vector3_scale(t_vector3 v, double k)
{
	return (t_vector3){ v.x * k, v.y * k, v.z * k };
}

t_vector3	vector3_divide_scalar(t_vector3 v, double k)
{
	return (t_vector3){ v.x / k, v.y / k, v.z / k };
}

t_vector3	vector3_add_scaled(t_vector3 a, t_vector3 b, double k)
{
	return (t_vector3){ a.x + k*b.x, a.y + k*b.y, a.z + k*b.z };
}

/* === Arithmetic (component-wise) === */

t_vector3	vector3_multiply_componentwise(t_vector3 a, t_vector3 b)
{
	return (t_vector3){ a.x * b.x, a.y * b.y, a.z * b.z };
}

t_vector3	vector3_divide_componentwise(t_vector3 a, t_vector3 b)
{
	return (t_vector3){ a.x / b.x, a.y / b.y, a.z / b.z };
}

int	vector3_divide_componentwise_safe(t_vector3 a, t_vector3 b, double eps, t_vector3 *out)
{
	if (fabs(b.x) <= eps || fabs(b.y) <= eps || fabs(b.z) <= eps) {
		*out = VECTOR3_ZERO;
		return 0;
	}
	*out = (t_vector3){ a.x / b.x, a.y / b.y, a.z / b.z };
	return 1;
}

/* === Norms / normalization === */

double	vector3_length_squared(t_vector3 v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

double	vector3_length(t_vector3 v)
{
	return sqrt(vector3_length_squared(v));
}

int	vector3_normalize_safe(t_vector3 v, t_vector3 *out, double eps)
{
	double len2 = vector3_length_squared(v);
	if (len2 <= eps*eps) {
		*out = VECTOR3_ZERO;
		return 0;
	}
	double inv = 1.0 / sqrt(len2);
	*out = (t_vector3){ v.x*inv, v.y*inv, v.z*inv };
	return 1;
}

/* === Dot product / Cross product === */

double	vector3_dot(t_vector3 a, t_vector3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

t_vector3	vector3_cross(t_vector3 a, t_vector3 b)
{
	return (t_vector3){
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	};
}

/* === Utilities === */

t_vector3	vector3_abs(t_vector3 v)
{
	return (t_vector3){ fabs(v.x), fabs(v.y), fabs(v.z) };
}

t_vector3	vector3_min(t_vector3 a, t_vector3 b)
{
	return (t_vector3){ fmin(a.x,b.x), fmin(a.y,b.y), fmin(a.z,b.z) };
}

t_vector3	vector3_max(t_vector3 a, t_vector3 b)
{
	return (t_vector3){ fmax(a.x,b.x), fmax(a.y,b.y), fmax(a.z,b.z) };
}

t_vector3	vector3_clamp(t_vector3 v, double mn, double mx)
{
	if (v.x < mn) v.x = mn; else if (v.x > mx) v.x = mx;
	if (v.y < mn) v.y = mn; else if (v.y > mx) v.y = mx;
	if (v.z < mn) v.z = mn; else if (v.z > mx) v.z = mx;
	return v;
}

t_vector3	vector3_lerp(t_vector3 a, t_vector3 b, double t)
{
	return (t_vector3){
		a.x*(1.0 - t) + b.x*t,
		a.y*(1.0 - t) + b.y*t,
		a.z*(1.0 - t) + b.z*t
	};
}
