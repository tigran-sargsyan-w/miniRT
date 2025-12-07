/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:46:49 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 18:50:21 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "vector.h"
# include "material.h"

struct	s_object;

typedef struct s_hit
{
	double					t;
	t_vector3				point;
	t_vector3				normal;
	const t_material		*material;
	const struct s_object	*object;
}							t_hit;

#endif
