#include "object.h"

void	object_init(t_object *object, t_object_type type, t_material material,
		t_intersect_func intersect_func,
		t_translate_func translate,
		t_rotate_euler_func rotate_euler,
		t_scale_func scale_uniform,
		t_scale_height_func scale_height)
{
	object->type = type;
	object->material = material;
	object->intersect_func = intersect_func;
	object->translate = translate;
	object->rotate_euler = rotate_euler;
	object->scale_uniform = scale_uniform;
	object->scale_height = scale_height;
}