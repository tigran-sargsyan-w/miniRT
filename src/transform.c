#include <math.h>
#include "transform.h"

// Rotate vector by Euler angles (rx, ry, rz) in radians, order: Rz * Ry * Rx
// Note: this matches the previous inline implementation
// Rx, then Ry, then Rz
// Returns rotated vector
// Uses right-handed coordinate system
// Safe for any finite angles

t_vector3 rotate_euler_vec(t_vector3 v, double rx, double ry, double rz)
{
    t_vector3 t;
    double cx = cos(rx), sx = sin(rx);
    double cy = cos(ry), sy = sin(ry);
    double cz = cos(rz), sz = sin(rz);
    // Rx
    t.x = v.x;
    t.y = v.y * cx - v.z * sx;
    t.z = v.y * sx + v.z * cx;
    // Ry
    v.x = t.x * cy + t.z * sy;
    v.y = t.y;
    v.z = -t.x * sy + t.z * cy;
    // Rz
    t.x = v.x * cz - v.y * sz;
    t.y = v.x * sz + v.y * cz;
    t.z = v.z;
    return t;
}
