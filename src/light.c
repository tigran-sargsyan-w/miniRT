#include "light.h"
#include "color.h"

t_light	light_point_make(t_vector3 position, t_color8 color, double intensity)
{
	t_light light;

	light.position = position;
	light.color = color;
	light.intensity = intensity;
	return (light);
}