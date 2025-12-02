/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:39:44 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/02 22:45:40 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "color.h"
# include "vector.h"

typedef struct s_light		t_light;
typedef struct s_light_node	t_light_node;

struct						s_light
{
	t_vector3				position;
	t_color8				color;
	double intensity; // 0..∞
};

// Linked list node for lights
typedef struct s_light_node
{
	t_light					*light;
	struct s_light_node		*next;
}							t_light_node;

#endif
