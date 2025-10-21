/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsemenov <dsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:36:20 by tsargsya          #+#    #+#             */
/*   Updated: 2025/10/21 05:33:01 by dsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "types.h"

int check_args(int argc, char **argv);
int check_parse_file(int fd, struct s_scene *scene);
int validate_input_range(t_scene *scene);
void	debug_print_scene(t_scene *scene);

#endif