/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_man.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 13:44:30 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_close(t_img *img)
{
	free_img(img);
	exit(img->error);
}

int	key_handler(int key, t_img *img)
{
	if (key == MAIN_PAD_ESC)
		ft_close(img);
	else if (key == MAIN_PAD_H)
		ft_toggle_help(img);
	return (0);
}

int	mouse_handler(int mouse_action, int x, int y, t_img *img)
{
	if (mouse_action == MOUSE_SCROLL_DOWN || mouse_action == MOUSE_SCROLL_UP)
		ft_focal(mouse_action, x, y, img);
	return (0);
}
