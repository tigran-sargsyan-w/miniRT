#ifndef TYPES_H
# define TYPES_H

# include "light.h"
# include "sphere.h"

typedef struct s_ambient
{
    float intensity;
    int color[3];
}   t_ambient;

typedef struct s_camera
{
    float position[3];
    float orientation[3];
    int fov;
}   t_camera;

typedef struct s_plane
{
    float point[3];
    float normal[3];
    int color[3];
}   t_plane;

typedef struct s_cylinder
{
    float center[3];
    float orientation[3];
    float diameter;
    float height;
    int color[3];
}   t_cylinder;

typedef struct s_scene
{
    int has_ambient;
    t_ambient ambient;
    int has_camera;
    t_camera camera;
    int has_light;
    t_light light;
    t_sphere *spheres;
    int sphere_count;
    t_plane *planes;
    int plane_count;
    t_cylinder *cylinders;
    int cylinder_count;
}   t_scene;

#endif