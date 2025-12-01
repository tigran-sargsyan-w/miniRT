/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:46:58 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/01 23:46:59 by dsemenov         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
