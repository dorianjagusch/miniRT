/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 22:04:23 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"
//set loop in per pixel function for bounces and modify ray in hitshader or call relect function
// and reassign ray while saving the colour
perpixel(t_img *img, t_vec2 pxl)
{
	t_ray		ray;
	t_payload	payload;

	while (i < BOUNCES)
	{
		ray.origin = img->scene.cam.pos;
		//ray.direction = (((pxl.x + pxl.y * WIDTH) / TOTAL) * 2) - 1;
		get_closest(&(img->scene), &ray, &payload);
		if (payload.distance == DBL_MAX)
			return (miss());
		ray.colour += hit_shader(img->scene, payload, ray);
		ray.direction = ft_v3multf(ray.direction, -1),
		ray.direction = ft_v3reflect(ray.direction, payload.hitnorm);
		ray.origin = payload.hitpoint + payload.hitnorm * 0.0001;
	}
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
	int		tot_res;

	tot_res = HEIGHT * WIDTH;
	pxl.y = 0;
	while (pxl.y < HEIGHT)
	{
		pxl.x = 0;
		while (pxl.x < WIDTH)
		{
			my_mlx_pixel_put(img, pxl, perpixel(img, pxl));
			pxl.x++;
		}
		pxl.y++;
	}
	mlx_put_image_to_window(img->win->mlx, img->win->win, img->img, 0, 0);
	mlx_string_put(img->win->mlx, img->win->win, WIDTH - 80,
		20, WHITE, "[H] - Help");
}
