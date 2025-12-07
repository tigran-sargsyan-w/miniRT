/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:46:42 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/07 17:58:11 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define M_PI 3.14159265358979323846
# define RT_EPS 1e-9
# define RT_MIN_OBJECT_EXTENT 1e-6
# define K_TMIN_PRIMARY 1e-6
# define K_TMAX_PRIMARY 1e6
# define K_SKY_BLEND_BIAS 0.5
# define K_SHADOW_BIAS 1e-4

# define KEY_ESCAPE 65307

// Scale control keys
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

// Translation control keys
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101

// Rotations control keys
# define KEY_I 105
# define KEY_K 107
# define KEY_J 106
# define KEY_L 108
# define KEY_U 117
# define KEY_O 111

// Transform steps
# ifndef MOVE_STEP
#  define MOVE_STEP 0.25
# endif
# ifndef ROTATE_STEP_DEG
#  define ROTATE_STEP_DEG 5.0
# endif
# ifndef SCALE_STEP
#  define SCALE_STEP 1.05
# endif

#endif
