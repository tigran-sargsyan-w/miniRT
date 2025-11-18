#include "trace.h"
#include "object.h"

int scene_intersect(const t_scene *scene, t_ray ray, double t_min, double t_max, t_hit *out_hit)
{
    t_hit   temp_hit;
    double  closest = t_max;
    int     hit_any = 0;
    int     i;

    /* Spheres */
    i = 0;
    while (i < scene->sphere_count)
    {
        const t_object *obj = (const t_object *)&scene->spheres[i];
        if (obj->intersect_func &&
            obj->intersect_func(obj, ray, t_min, closest, &temp_hit))
        {
            hit_any = 1;
            closest = temp_hit.t;
            *out_hit = temp_hit;
            out_hit->object = obj;
        }
        i++;
    }

    /* Planes */
    i = 0;
    while (i < scene->plane_count)
    {
        const t_object *obj = (const t_object *)&scene->planes[i];
        if (obj->intersect_func &&
            obj->intersect_func(obj, ray, t_min, closest, &temp_hit))
        {
            hit_any = 1;
            closest = temp_hit.t;
            *out_hit = temp_hit;
            out_hit->object = obj;
        }
        i++;
    }

    /* Cylinders */
    i = 0;
    while (i < scene->cylinder_count)
    {
        const t_object *obj = (const t_object *)&scene->cylinders[i];
        if (obj->intersect_func &&
            obj->intersect_func(obj, ray, t_min, closest, &temp_hit))
        {
            hit_any = 1;
            closest = temp_hit.t;
            *out_hit = temp_hit;
            out_hit->object = obj;
        }
        i++;
    }

    return hit_any;
}

// Fast boolean occlusion query: returns 1 as soon as any hit is found in (t_min, t_max)
int scene_occluded(const t_scene *scene, t_ray ray, double t_min, double t_max)
{
    t_hit   temp_hit;
    int     i;

    // Spheres
    i = 0;
    while (i < scene->sphere_count)
    {
        const t_object *obj = (const t_object *)&scene->spheres[i];
        if (obj->intersect_func && obj->intersect_func(obj, ray, t_min, t_max, &temp_hit))
            return 1;
        i++;
    }

    // Planes
    i = 0;
    while (i < scene->plane_count)
    {
        const t_object *obj = (const t_object *)&scene->planes[i];
        if (obj->intersect_func && obj->intersect_func(obj, ray, t_min, t_max, &temp_hit))
            return 1;
        i++;
    }

    // Cylinders
    i = 0;
    while (i < scene->cylinder_count)
    {
        const t_object *obj = (const t_object *)&scene->cylinders[i];
        if (obj->intersect_func && obj->intersect_func(obj, ray, t_min, t_max, &temp_hit))
            return 1;
        i++;
    }

    return 0;
}
