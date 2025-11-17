#ifndef TRACE_H
#define TRACE_H

#include "scene.h"
#include "ray.h"
#include "hit.h"

int scene_intersect(const t_scene *scene, t_ray ray, double t_min, double t_max, t_hit *out_hit);

#endif
