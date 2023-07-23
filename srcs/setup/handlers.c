/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 14:14:25 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TODO: REMOVE ALL THIS FOR BONUS TOO AFTER DEBUGGING
int	ft_close(t_img *img)
{
	free_img(img);
	exit(img->error);
}

int	key_handler(int key, t_img *img)
{
	if (key == MAIN_PAD_ESC)
		ft_close(img);
	else if (key == MAIN_PAD_SPACE)
		ft_toggle_move(img);
	else if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS)
		ft_change_bounces(img, key);
	else if (key == MAIN_PAD_H)
		ft_toggle_help(img);
	else if (key == MAIN_PAD_UP || key == MAIN_PAD_DOWN
		|| key == MAIN_PAD_LEFT || key == MAIN_PAD_RIGHT
		|| key == MAIN_PAD_S || key == MAIN_PAD_W
		|| key == MAIN_PAD_A || key == MAIN_PAD_D)
		camera_move(key, img);
	return (0);
}

int	mouse_handler(int mouse_action, int x, int y, t_img *img)
{
	if (mouse_action == MOUSE_SCROLL_DOWN || mouse_action == MOUSE_SCROLL_UP)
		ft_focal(mouse_action, x, y, img);
	// if (mouse_action == MOUSE_LEFT)
	// 	mlx_hook(img->win.win, ON_MOUSEMOVE, (1L << 6), mouse_position, img);
	return (0);
}
