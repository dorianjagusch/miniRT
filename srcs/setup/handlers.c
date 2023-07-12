/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/12 14:56:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_(int x, int y, t_img *img)
{
	return (0);
}

int	ft_close(t_img *img)
{
	free_img(img);
	exit(img->error);
}

// int	ft_close_win(t_img *img)
// {
// 	static int		start;
// 	static u_int8_t	active;

// 	if (!start)
// 	{
// 		active = (img->win_num * img->win_num) - 1;
// 		start++;
// 	}
// 	img->active = 0;
// 	set_active(img, &active);
// 	free_img(img);
// 	if (!active)
// 		ft_close(0);
// 	return (0);
// }

int	key_handler(int key, t_img *img)
{
	//printf("%d\n", key);
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
	return (0);
}
