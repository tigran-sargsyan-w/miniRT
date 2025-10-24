#include <material.h>

t_material	material_from_rgb8(t_color8 rgb)
{
	t_material material;

	material.base_color = color_from_rgb8(rgb);
	return (material);
}