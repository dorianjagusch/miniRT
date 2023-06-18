/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 19:11:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int32_t ft_trace(t_img *img, double coord)
{
	return (0xFF00AA);
}

static void	my_mlx_pixel_put(t_img *img, t_vec2 pxl, int colour)
{
	char	*dst;

	dst = img->addr + ((int)pxl.y * img->line_length
			+ (int)pxl.y * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	render(t_img *img)
{
	t_vec2	pxl;
	double	coord;
	int		tot_res;

	tot_res = HEIGHT * WIDTH;
	pxl.y = 0;
	while (pxl.y < HEIGHT)
	{
		pxl.x = 0;
		while (pxl.x < WIDTH)
		{
			coord = pxl.x + WIDTH * pxl.y;
			my_mlx_pixel_put(img, pxl, ft_trace(img, coord));
			pxl.y++;
		}
		pxl.y++;
	}
	mlx_put_image_to_window(img->win->mlx, img->win->win, img->img, 0, 0);
	mlx_string_put(img->win->mlx, img->win->win, WIDTH - 80,
		20, WHITE, "[H] - Help");
}
