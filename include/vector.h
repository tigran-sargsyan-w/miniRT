#ifndef VECTOR_H
#define VECTOR_H

#define M_PI 3.14159265358979323846

typedef struct s_vector3
{
    double x;
    double y;
    double z;
} t_vector3;

t_vector3 vec_create(double x, double y, double z);
t_vector3 vec_add(t_vector3 a, t_vector3 b);
t_vector3 vec_sub(t_vector3 a, t_vector3 b);
t_vector3 vec_scale(t_vector3 v, double s);
double vec_dot(t_vector3 a, t_vector3 b);
double vec_length(t_vector3 v);
t_vector3 vec_normalize(t_vector3 v);
// additional utilities
t_vector3 vec_mul(t_vector3 a, t_vector3 b); // component-wise multiply
t_vector3 vec_div_s(t_vector3 v, double s);
double vec_len2(t_vector3 v);
t_vector3 vec_cross(t_vector3 a, t_vector3 b);
int vec_near_zero(t_vector3 v); // returns 1 if near zero
t_vector3 vec_reflect(t_vector3 v, t_vector3 n);

// math helpers
double deg2rad(double deg);

// robust quadratic solver
// solves ax^2 + bx + c = 0. returns number of real roots (0,1,2).
// if roots != NULL it will be filled with up to 2 roots (roots[0] <= roots[1]).
int solve_quadratic(double a, double b, double c, double roots[2]);

#endif