#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector.h"

// Rotate vector by Euler angles (rx, ry, rz) in radians, order: Rz * Ry * Rx
t_vector3 rotate_euler_vec(t_vector3 v, double rx, double ry, double rz);

#endif
