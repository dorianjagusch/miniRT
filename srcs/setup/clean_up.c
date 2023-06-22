/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/22 13:30:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_img(t_img *img)
{
	if (img->bits & IMG_INIT)
		mlx_destroy_image(img->win->mlx, img->img);
	if (img->bits & WIN_WIN_INIT)
		mlx_destroy_window(img->win->mlx, img->win->win);
	if (img->bits & WIN_INIT)
		free(img->win);
	if (img->bits & OBJ_INIT)
		free(img->win);
}
