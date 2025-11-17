#include <math.h>
#include <stdlib.h>
#include "miniRT.h"
#include "object.h"
#include "vector.h"
#include "color.h"
#include "ray.h"
#include "hit.h"
#include "camera.h"
#include "material.h"
#include "constants.h"

// Convert linear t_color to packed int (X11 expected endian: assume 0x00RRGGBB)
static int color_to_int(t_color c)
{
    t_color8 srgb = color_to_rgb8(color_clamp01(c));
    return ((srgb.r << 16) | (srgb.g << 8) | (srgb.b));
}

static int scene_intersect(const t_scene *scene, t_ray ray, double t_min, double t_max, t_hit *out_hit)
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
        }
        i++;
    }

    return hit_any;
}

// Very simple pseudo-random (linear congruential generator).
static double rand01(unsigned int *seed)
{
    *seed = *seed * 1664525u + 1013904223u;
    return (double)(*seed & 0x00FFFFFF) / (double)0x01000000;
}

// Small random direction vector with length <= 1
static t_vector3 random_unit_sphere(unsigned int *seed)
{
    t_vector3 v;
    double    len2;

    while (1)
    {
        v.x = 2.0 * rand01(seed) - 1.0;
        v.y = 2.0 * rand01(seed) - 1.0;
        v.z = 2.0 * rand01(seed) - 1.0;
        len2 = v.x * v.x + v.y * v.y + v.z * v.z;
        if (len2 > 0.0 && len2 <= 1.0)
            return v;
    }
}

// Returns visibility in [0, 1]
static double soft_shadow_visibility(const t_scene *scene, const t_hit *hit)
{
    unsigned int seed = 123456u; // you can mix in something from hitPoint here for variation
    int          unoccluded = 0;
    int          i;

    i = 0;
    while (i < SHADOW_SAMPLES)
    {
        // Slightly jitter the light source position
        t_vector3 jitter = random_unit_sphere(&seed);
        jitter = vector3_scale(jitter, LIGHT_RADIUS);
        t_vector3 light_pos = vector3_add(scene->light.position, jitter);

        // Construct ray toward the jittered (shifted) light source
        t_vector3 L = vector3_subtract(light_pos, hit->hitPoint);
        double    dist = vector3_length(L);
        t_vector3 L_unit;

        if (!vector3_normalize_safe(L, &L_unit, RT_EPS))
        {
            i++;
            continue;
        }

        t_vector3 shadow_origin = vector3_add(hit->hitPoint,
                                vector3_scale(hit->normal, K_SHADOW_BIAS));
        t_ray shadow_ray = ray_make(shadow_origin, L_unit);
        t_hit tmp_hit;

        // If NOTHING intercepted the ray before the light — consider this sample sees the light
        if (!scene_intersect(scene, shadow_ray,
                K_TMIN_PRIMARY, dist - K_SHADOW_BIAS, &tmp_hit))
        {
            unoccluded++;
        }
        i++;
    }
    return (double)unoccluded / (double)SHADOW_SAMPLES;
}

static t_color shade(const t_scene *scene, const t_hit *hit)
{
    // Ambient + single light diffuse (Lambert). No shadows yet.
    t_color base = hit->material->base_color;
    t_color ambient_lin = color_scale(color_from_rgb8(scene->ambient.color), scene->ambient.intensity);
    t_color result = color_multiply(base, ambient_lin);
    if (!scene->has_light || !hit || !hit->material)
        return result;

    // light color linear
    t_color light_color = color_from_rgb8(scene->light.color);

    // direction to light
    t_vector3 L = vector3_subtract(scene->light.position, hit->hitPoint);
    t_vector3 L_unit;
    if (!vector3_normalize_safe(L, &L_unit, RT_EPS))
        return result;

    // compute soft-shadow visibility
    double visibility = soft_shadow_visibility(scene, hit);
    if (visibility <= 0.0)
        return result;

    double ndotl = vector3_dot(hit->normal, L_unit);
    if (ndotl > 0.0)
    {
        double diffuse = ndotl * scene->light.intensity * visibility;
        if (diffuse < 0.0) diffuse = 0.0;
        result = color_add(result, color_scale(color_multiply(base, light_color), diffuse));
    }
    return result;
}

static t_color trace_ray(const t_scene *scene, t_ray ray)
{
    t_hit hit;

    if (scene_intersect(scene, ray, K_TMIN_PRIMARY, K_TMAX_PRIMARY, &hit))
        return shade(scene, &hit);

    // Background gradient
    const double t = K_SKY_BLEND_BIAS * (ray.dir.y + 1.0);
    const t_color sky_top    = color_make(0.5, 0.5, 0.5);
    const t_color sky_bottom = color_make(0.0, 0.0, 0.0);
    return color_lerp(sky_bottom, sky_top, t);
}

int render_scene(t_data *data)
{
    int x,y;
    t_camera cam;

    if (!data)
        return 1;
    // Initialize camera using parsed scene camera orientation as forward
    if (!data->scene.has_camera)
        return 1;
    if (camera_init(&cam, data->scene.camera.position, data->scene.camera.orientation,
            data->scene.camera.fov, WIDTH, HEIGHT))
        return 1;
    // Cache into scene camera basis (optional if later needed)
    data->scene.camera.forward = cam.forward;
    data->scene.camera.right = cam.right;
    data->scene.camera.up = cam.up;
    data->scene.camera.half_width = cam.half_width;
    data->scene.camera.half_height = cam.half_height;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            t_ray ray = camera_ray(&cam, x, y, WIDTH, HEIGHT);
            t_color col = trace_ray(&data->scene, ray);
            int packed = color_to_int(col);
            my_mlx_pixel_put(&data->mlx.img, x, y, packed);
            x++;
        }
        y++;
    }
    return 0;
}
