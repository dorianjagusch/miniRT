/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 12:34:26 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	user_input(t_img *img)
{
	ft_printf("segfault marker- in user input\n");
	mlx_key_hook(img->win, key_handler, img);
	ft_printf("segfault marker\n");
	mlx_mouse_hook(img->win, mouse_handler, img);
	ft_printf("segfault marker\n");
	mlx_hook(img->win, ON_DESTROY, 1L << 0, ft_close_win, img);
	 ft_printf("segfault marker- before return in user input\n"); // if MLX is 
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
