#ifndef VECTOR_H
#define VECTOR_H

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

#endif