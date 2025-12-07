/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:39:44 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 18:50:53 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "color.h"
# include "vector.h"

typedef struct s_light		t_light;

struct						s_light
{
	t_vector3				position;
	t_color8				color;
	double					intensity;
};

#endif
