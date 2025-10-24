// scene.c
#include <stdlib.h>
#include "scene.h"

static void	free_object_list(t_object_node *objectNode)
{
	t_object_node *current;
	t_object_node *next;

	current = objectNode;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static void	free_light_list(t_light_node *lightNode)
{
	t_light_node *current;
	t_light_node *next;

	current = lightNode;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	scene_init(t_scene *scene, t_color ambient, t_camera camera)
{
	scene->ambient = ambient;
	scene->camera = camera;
	scene->objects = NULL;
	scene->lights = NULL;
	scene->object_count = 0;
	scene->light_count = 0;
}

void	scene_clear(t_scene *scene)
{
	if (!scene)
		return ;
	free_object_list(scene->objects);
	free_light_list(scene->lights);
	scene->objects = NULL;
	scene->lights = NULL;
	scene->object_count = 0;
	scene->light_count = 0;
}

int	scene_add_object(t_scene *scene, const t_object *object)
{
	t_object_node *node;

	if (!scene || !object)
		return (1);
	node = (t_object_node *)malloc(sizeof(*node));
	if (!node)
		return (1);
	node->object = object;
	node->next = scene->objects;
	scene->objects = node;
	scene->object_count++;
	return (0);
}

int	scene_add_light(t_scene *scene, const t_light *light)
{
	t_light_node *node;

	if (!scene || !light)
		return (1);
	node = (t_light_node *)malloc(sizeof(*node));
	if (!node)
		return (1);
	node->light = light;
	node->next = scene->lights;
	scene->lights = node;
	scene->light_count++;
	return (0);
}
