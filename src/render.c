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
#include "trace.h"

// Convert linear t_color to packed int (X11 expected endian: assume 0x00RRGGBB)
static int color_to_int(t_color c)
{
    t_color8 srgb = color_to_rgb8(color_clamp01(c));
    return ((srgb.r << 16) | (srgb.g << 8) | (srgb.b));
}

// scene_intersect is now provided by trace.c

// Returns 1 if some object blocks light between hit point and light
static int is_in_shadow(const t_scene *scene, const t_hit *hit)
{
    t_vector3 L;
    double    dist;
    t_vector3 L_unit;
    t_vector3 shadow_origin;
    t_ray     shadow_ray;
    t_hit     tmp_hit;

    L = vector3_subtract(scene->light.position, hit->hitPoint);
    dist = vector3_length(L);
    if (!vector3_normalize_safe(L, &L_unit, RT_EPS))
        return (0);
    shadow_origin = vector3_add(hit->hitPoint,
            vector3_scale(hit->normal, K_SHADOW_BIAS));
    shadow_ray = ray_make(shadow_origin, L_unit);
    if (scene_intersect(scene, shadow_ray,
            K_TMIN_PRIMARY, dist - K_SHADOW_BIAS, &tmp_hit))
        return (1);
    return (0);
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

    // hard shadow: if blocked, keep only ambient
    if (is_in_shadow(scene, hit))
        return result;

    double ndotl = vector3_dot(hit->normal, L_unit);
    if (ndotl > 0.0)
    {
        double diffuse = ndotl * scene->light.intensity;
        if (diffuse < 0.0) diffuse = 0.0;
        result = color_add(result, color_scale(color_multiply(base, light_color), diffuse));
    }
    return result;
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

    // Allocate object buffer for outline pass once and reuse between frames
    if (!data->objbuf)
    {
        data->objbuf = (const t_object **)malloc(sizeof(*data->objbuf)
                * WIDTH * HEIGHT);
        if (!data->objbuf)
            return 1;
    }

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            t_ray ray = camera_ray(&cam, x, y, WIDTH, HEIGHT);
            t_hit htmp;
            t_color col;
            if (scene_intersect(&data->scene, ray, K_TMIN_PRIMARY, K_TMAX_PRIMARY, &htmp))
            {
                data->objbuf[y * WIDTH + x] = htmp.object;
                col = shade(&data->scene, &htmp);
            }
            else
            {
                data->objbuf[y * WIDTH + x] = NULL;
                const double tb = K_SKY_BLEND_BIAS * (ray.dir.y + 1.0);
                const t_color sky_top    = color_make(0.5, 0.5, 0.5);
                const t_color sky_bottom = color_make(0.0, 0.0, 0.0);
                col = color_lerp(sky_bottom, sky_top, tb);
            }
            int packed = color_to_int(col);
            my_mlx_pixel_put(&data->mlx.img, x, y, packed);
            x++;
        }
        y++;
    }

    // Simple 1px outline for selected object
    if (data->selected_object)
    {
        const int outline = 0x00FFFF00; // yellow
        y = 0;
        while (y < HEIGHT)
        {
            x = 0;
            while (x < WIDTH)
            {
            const t_object *o = data->objbuf[y * WIDTH + x];
                if (o == data->selected_object)
                {
                    int edge = 0;
                    if (x <= 0 || data->objbuf[y * WIDTH + (x - 1)] != data->selected_object) edge = 1;
                    else if (x >= WIDTH - 1 || data->objbuf[y * WIDTH + (x + 1)] != data->selected_object) edge = 1;
                    else if (y <= 0 || data->objbuf[(y - 1) * WIDTH + x] != data->selected_object) edge = 1;
                    else if (y >= HEIGHT - 1 || data->objbuf[(y + 1) * WIDTH + x] != data->selected_object) edge = 1;
                    if (edge)
                        my_mlx_pixel_put(&data->mlx.img, x, y, outline);
                }
                x++;
            }
            y++;
        }
    }
    return 0;
}
