/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:00:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/12/06 22:51:09 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_INTERNAL_H
# define EVENT_INTERNAL_H

# include "miniRT.h"

int		handle_escape(t_data *data);
int		handle_translation(t_data *data, int keycode);
int		handle_rotation(t_data *data, int keycode);
int		handle_scaling(t_data *data, int keycode);
void	render_and_display(t_data *data);
int		on_keypress(int keycode, void *param);
int		on_mouse(int button, int x, int y, void *param);

#endif
