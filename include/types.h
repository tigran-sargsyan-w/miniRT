#ifndef TYPES_H
# define TYPES_H

typedef enum e_object_type
{
    AMBIENT,
    CAMERA,
    LIGHT,
    SPHERE,
    PLANE,
    CYLINDER
}   t_object_type;

typedef struct s_ambient
{
    float intensity;
    int color[3];
}   t_ambient;

typedef struct s_camera
{
    float position[3];
    float orientation[3];
    float fov;
}   t_camera;

typedef struct s_light
{
    float position[3];
    float intensity;
    int color[3];
}   t_light;

typedef struct s_sphere
{
    float center[3];
    float radius;
    int color[3];
}   t_sphere;

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
    t_ambient ambient;
    t_camera camera;
    t_light *lights;
    t_sphere *spheres;
    int sphere_count;
    t_plane *planes;
    int plane_count;
    t_cylinder *cylinders;
    int cylinder_count;
}   t_scene;

#endif