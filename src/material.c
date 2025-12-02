/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:53:31 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/02 22:59:15 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <material.h>

/**
 * @brief Create a material from an 8-bit RGB color.
 * @param rgb The 8-bit RGB color.
 * @return The created material with base color converted to linear space.
 */
t_material	material_from_rgb8(t_color8 rgb)
{
	t_material	material;

	material.base_color = color_from_rgb8(rgb);
	return (material);
}
