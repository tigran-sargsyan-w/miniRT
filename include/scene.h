#ifndef SCENE_H
# define SCENE_H

# include <stddef.h>
# include "camera.h"
# include "object.h"
# include "light.h"
# include "color.h"
# include "hit.h"

typedef struct s_scene
{
	t_color     ambient;    // linear 0..1 (ambient light color)
	t_camera    camera;

	t_object_node  *objects;
	t_light_node   *lights;

	size_t      object_count;
	size_t      light_count;
}	t_scene;

// Initialize or clear scene.
void	scene_init(t_scene *scene, t_color ambient, t_camera cam);
void	scene_clear(t_scene *scene);

// Add object or light to the scene.
int		scene_add_object(t_scene *scene, const t_object *object);
int		scene_add_light(t_scene *scene, const t_light *light);

#endif