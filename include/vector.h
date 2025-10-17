#ifndef VECTOR_H
#define VECTOR_H

#define M_PI 3.14159265358979323846

typedef struct s_vector
{
    float x;
    float y;
    float z;
} t_vector;

t_vector vec_create(float x, float y, float z);
t_vector vec_add(t_vector a, t_vector b);
t_vector vec_sub(t_vector a, t_vector b);
t_vector vec_scale(t_vector v, float s);
float vec_dot(t_vector a, t_vector b);
float vec_length(t_vector v);
t_vector vec_normalize(t_vector v);
// additional utilities
t_vector vec_mul(t_vector a, t_vector b); // component-wise multiply
t_vector vec_div_s(t_vector v, float s);
float vec_len2(t_vector v);
t_vector vec_cross(t_vector a, t_vector b);
int vec_near_zero(t_vector v); // returns 1 if near zero
t_vector vec_reflect(t_vector v, t_vector n);

// math helpers
float deg2rad(float deg);

// robust quadratic solver
// solves ax^2 + bx + c = 0. returns number of real roots (0,1,2).
// if roots != NULL it will be filled with up to 2 roots (roots[0] <= roots[1]).
int solve_quadratic(float a, float b, float c, float roots[2]);

#endif