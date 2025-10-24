#ifndef MATERIAL_H
# define MATERIAL_H
# include "color.h"

typedef struct s_material
{
	t_color	base_color; /* linear 0..1 */
}	t_material;

// construct material from sRGB 0..255 color
t_material	material_from_rgb8(t_color8 rgb);
#endif
