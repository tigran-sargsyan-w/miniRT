/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 23:46:42 by dsemenov          #+#    #+#             */
/*   Updated: 2025/12/06 23:28:57 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef RT_EPS
#  define RT_EPS 1e-9
# endif

# ifndef RT_MIN_OBJECT_EXTENT
#  define RT_MIN_OBJECT_EXTENT 1e-6
# endif

# ifndef K_TMIN_PRIMARY
#  define K_TMIN_PRIMARY 1e-6
# endif

# ifndef K_TMAX_PRIMARY
#  define K_TMAX_PRIMARY 1e6
# endif

# ifndef K_SKY_BLEND_BIAS
#  define K_SKY_BLEND_BIAS 0.5
# endif

# ifndef K_SHADOW_BIAS
#  define K_SHADOW_BIAS 1e-4
# endif

# ifndef KEY_ESCAPE
#  define KEY_ESCAPE 65307
# endif

// Scale control keys
# ifndef KEY_LEFT
#  define KEY_LEFT 65361
# endif
# ifndef KEY_UP
#  define KEY_UP 65362
# endif
# ifndef KEY_RIGHT
#  define KEY_RIGHT 65363
# endif
# ifndef KEY_DOWN
#  define KEY_DOWN 65364
# endif

// WASDQE for 3D translation
# ifndef KEY_W
#  define KEY_W 119
# endif
# ifndef KEY_A
#  define KEY_A 97
# endif
# ifndef KEY_S
#  define KEY_S 115
# endif
# ifndef KEY_D
#  define KEY_D 100
# endif
# ifndef KEY_Q
#  define KEY_Q 113
# endif
# ifndef KEY_E
#  define KEY_E 101
# endif

// Rotations: I/K around X, J/L around Y, U/O around Z
# ifndef KEY_I
#  define KEY_I 105
# endif
# ifndef KEY_K
#  define KEY_K 107
# endif
# ifndef KEY_J
#  define KEY_J 106
# endif
# ifndef KEY_L
#  define KEY_L 108
# endif
# ifndef KEY_U
#  define KEY_U 117
# endif
# ifndef KEY_O
#  define KEY_O 111
# endif

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
