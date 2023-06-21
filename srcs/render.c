/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/21 22:35:59 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	miss(t_img *img)
{

}

//set loop in per pixel function for bounces and modify ray in hitshader or call relect function
// and reassign ray while saving the colour
int32_t	perpixel(t_img *img, t_vec2 pxl)
{
	t_ray		ray;
	t_payload	payload;
	t_vec4		colour;
	int			i;

	i = 0;
	ray.origin = img->scene.cam.pos;
	//ray.direction = (((pxl.x + pxl.y * WIDTH) / TOTAL) * 2) - 1;
	while (i < BOUNCES)
	{
		get_closest(&(img->scene), &ray, &payload);
		if (payload.distance == DBL_MAX)
		{
			colour = ft_v4add(colour, miss(img));
			break;
		}
		colour = ft_v4add(colour, hit_shader(&(img->scene), &payload));
		ray.direction = ft_v3multf(ray.direction, -1),
		ray.direction = ft_v3reflect(ray.direction, payload.hitnorm);
		ray.origin = ft_v3add(payload.hitpoint, ft_v3multf(payload.hitnorm, 0.0001));
		i++;
	}
	ft_v4clamp(&colour, 0, 1);
	return (ft_v4toint32(colour));
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
