#ifndef OBJECT_H
# define OBJECT_H
# include "hit.h"
# include "ray.h"

typedef struct s_object			t_object;
typedef struct s_object_node	t_object_node;

// Intersection interface: return 1 if there is a hit in [t_min,t_max].
typedef int (*t_intersect_func)(const t_object *object,
								t_ray ray,
								double t_min,
								double t_max,
								t_hit *hit_result);

typedef enum e_obj_type
{
	OBJ_SPHERE = 1,
	OBJ_PLANE = 2,
	OBJ_CYL = 3
}								t_obj_type;

// Base class (first field in "derived" structs)
struct							s_object
{
	t_obj_type					type;
	t_intersect_func			intersect_func;
	t_material					material;
};

// Linked list node for objects
struct							s_object_node
{
	const t_object *object;
	struct s_object_node		*next;
};

void							object_init(t_object *object, t_obj_type type,
									t_material material,
									t_intersect_func intersect_func);

#endif
