/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/25 23:10:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_options(void)
{
	ft_printf("\n\t*********************\n");
	ft_printf("\t****   Options   ****\n");
	ft_printf("\t*********************\n\n");
	ft_printf("\n");
	exit (0);
}

void	draw_help(t_img *img)
{
	ft_bzero(img->addr, img->bits_per_pixel / 8 * WIDTH * HEIGHT);
	mlx_put_image_to_window(img->win.mlx, img->win.win, img->img, 0, 0);
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 30,
		HEIGHT * 0.33, WHITE, "CONTROLS");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 20, WHITE, "[C]/[X]          Change colour");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 40, WHITE, "[+]/[-] NUM PAD  Rotate");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 60, WHITE, "LEFT MOUSE       Centre of rotation");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 80, WHITE, "[0-3] KEYS       Switch fractal");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 100, WHITE, "[+]/[-] KEYS     Change iterations");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 120, WHITE, "ARROW KEYS       Move on the fractal");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 140, WHITE, "MOUSE WHEEL      Zoom");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 160, WHITE, "[SPACE]          Lock mouse position");
	mlx_string_put(img->win.mlx, img->win.win, WIDTH / 2 - 110,
		HEIGHT * 0.33 + 180, WHITE, "[R]              Reset");
}

int	ft_toggle_help(t_img *img)
{
	int	check;

	check = 0;
	if (img->is_help == 0)
		img->is_help = 1;
	else
		img->is_help = 0;
	if (!img->is_help)
		render(img);
	else
		draw_help(img);
	return (check);
}

// void	set_active(t_img *img, u_int8_t *active)
// {
// 	if (!img->active)
// 	{
// 		if (img->win_id == 0)
// 			*active ^= WIN_0;
// 		else if (img->win_id == 1)
// 			*active ^= WIN_1;
// 		else if (img->win_id == 2)
// 			*active ^= WIN_2;
// 		else if (img->win_id == 3)
// 			*active ^= WIN_3;
// 	}
// }
