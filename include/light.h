#ifndef LIGHT_H
# define LIGHT_H
# include "color.h"
# include "vector.h"

typedef struct s_light		t_light;
typedef struct s_light_node	t_light_node;

struct						s_light
{
	t_vector3				position;
	t_color color;    // linear 0..1
	double intensity; // 0..∞
};

// Linked list node for lights
typedef struct s_light_node
{
	t_light					light;
	struct s_light_node		*next;
}							t_light_node;

t_light						light_point_make(t_vector3 position, t_color8 color,
								double intensity);
#endif