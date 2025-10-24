#include "object.h"

void	object_init(t_object *object, t_obj_type type, t_material material,
		t_intersect_func intersect_func)
{
	object->type = type;
	object->material = material;
	object->intersect_func = intersect_func;
}