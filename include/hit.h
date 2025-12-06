/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:46:49 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/06 23:16:37 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "vector.h"
# include "material.h"

// Forward declaration to avoid circular include with object.h
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
