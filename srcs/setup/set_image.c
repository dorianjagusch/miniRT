/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/22 13:42:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	user_input(t_img *img)
{
	mlx_key_hook(img->win->win, key_handler, img);
	mlx_mouse_hook(img->win->win, mouse_handler, img);
	mlx_hook(img->win->win, ON_DESTROY, 1L << 0, ft_close_win, img);
	//mlx_hook(img->win->win, ON_MOUSEMOVE, (1L << 6), mouse_position, img);
	return (0);
}

static int	prep_image(t_img *img)
{
	int	check;

	img->img = mlx_new_image(img->win->mlx, WIDTH, HEIGHT);
	if (!img->img)
		return (ENOMEM);
	img->bits |= IMG_INIT;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (ENOMEM);
	img->bits |= ADDR_INIT;
	if (check)
		return (check);
	return (0);
}

void	set_image(t_img *img)
{
	int		i;
	void	*mlx;

	mlx = mlx_init();
	if (!mlx)
		ft_error(ENOMEM);
	img->win->win = mlx_new_window(img->win->mlx,
			WIDTH, HEIGHT, "miniRT");
	if (!img->win->win)
		ft_error (ENOMEM);
	img->bits |= WIN_WIN_INIT;
	prep_image(img);
}
