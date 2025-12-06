/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 23:31:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/03 00:15:11 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

/**
 * @brief Initialize an object with the given type, material, and functions.
 * @param object Pointer to the object to initialize.
 * @param type The type of the object.
 * @param material The material of the object.
 * @param funcs The function pointers for the object's operations.
 */
void	object_init(t_object *object, t_object_type type,
		t_material material, t_object_funcs funcs)
{
	object->type = type;
	object->material = material;
	object->intersect_func = funcs.intersect;
	object->translate = funcs.translate;
	object->rotate_euler = funcs.rotate_euler;
	object->scale_uniform = funcs.scale_uniform;
	object->scale_height = funcs.scale_height;
}
