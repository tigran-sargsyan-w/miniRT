#include "libft.h"
#include "parse.h"
#include "sphere.h"
#include "vector.h"
#include "color.h"
#include "material.h"
#include <stdio.h>
#include <stdlib.h>

static int	spheres_push(t_scene *s, t_sphere *sp)
{
	t_sphere	*arr;
    int         i;

	arr = malloc(sizeof(*arr) * (s->sphere_count + 1));
	if (!arr)
		return (1);
    i = 0;
    while (i < s->sphere_count)
    {
        arr[i] = s->spheres[i];
        i++;
    }
	arr[s->sphere_count] = *sp;
	free(s->spheres);
	s->spheres = arr;
	s->sphere_count++;
	return (0);
}

int	parse_sphere(char *line, t_scene *scene)
{
	int			n;
	char		**tab;
	t_sphere	sp;
	double		tmp_center[3];
	int			tmp_color[3];

	tab = ft_split(line, ' ');
	if (!tab)
		return (1);
	n = 0;
	while (tab[n])
		n++;
	if (n != 3)
	{
		ft_free_tab(tab);
		printf("Error\nInvalid number of parameters for sphere\n");
		return (1);
	}
	if (parse_vec3(tab[0], tmp_center) || parse_color(tab[2], tmp_color))
	{
		ft_free_tab(tab);
		return (1);
	}
	sp.center = vector3_create(tmp_center[0], tmp_center[1], tmp_center[2]);
	sp.color = color8_make((uint8_t)tmp_color[0], (uint8_t)tmp_color[1], (uint8_t)tmp_color[2]);
	{
		char *endptr = NULL;
		double val = ft_strtod(tab[1], &endptr);
		if (endptr == tab[1])
		{
			ft_free_tab(tab);
			printf("Error\nInvalid sphere diameter\n");
			return (1);
		}
		sp.diameter = val;
	}
	// initialize material/object base
	if (sphere_init(&sp, sp.center, sp.diameter, material_from_rgb8(sp.color)))
	{
		ft_free_tab(tab);
		return (1);
	}
	if (spheres_push(scene, &sp))
	{
		ft_free_tab(tab);
		return (1);
	}
	ft_free_tab(tab);
	return (0);
}
