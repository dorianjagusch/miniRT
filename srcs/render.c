/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/01 00:22:24 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	miss(t_img *img)
{
	return ((t_vec4){1, 0, 0, 0});
}

int32_t	perpixel(t_img *img, t_vec2 pxl)
{
	//TODO: the payload stuff should be split, hit_test and pixel struct so we can use const, debugging etc is easier when modular
	//TODO: deep dive into pure functions, potentially add that in starting here
	t_ray		ray;
	t_payload	payload;// should split into a hit test and pixel so that debugging is easier
	t_vec4		colour;
	int			i;
	
	i = 0;
	payload.light_dist = 0;
	colour = img->scene.amb.colour;
	ray = create_primary_ray(&img->scene.cam, pxl);
	while (i < BOUNCES)
	{
		get_closest(&(img->scene), &ray, &payload);
		if (payload.distance < DBL_MAX)
		{
			set_hitpoint(&(img->scene), &ray, &payload);
			light_distance(&(img->scene), &payload);
		}
		if (payload.distance == DBL_MAX)
		{
			colour = vec4_propadd(miss(img), colour, img->scene.amb.ratio);
			break ;
		}
		colour = vec4_compmult(colour, hit_shader(&(img->scene), &payload));
		ray.direction = vec3_multf(ray.direction, -1),
		ray.direction = vec3_reflect(ray.direction, payload.hitnorm);
		ray.origin = payload.hitpoint;
		i++;
	}
	vec4_clamp(&colour, 0, 1);
	return (vec4_toint32(colour));
}

static void	my_mlx_pixel_put(t_img *img, t_vec2 pxl, int colour)
{
	char		*dst;
	static int	i;

	dst = img->addr + ((int)pxl.y * img->line_length
			+ (int)pxl.x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	render(t_img *img)
{
	t_vec2		pxl;
	int			tot_res;
	int			colour;

	tot_res = HEIGHT * WIDTH;
	pxl.y = 0;
	while (pxl.y < HEIGHT)
	{
		pxl.x = 0;
		while (pxl.x < WIDTH)
		{
			colour = perpixel(img, pxl);
			my_mlx_pixel_put(img, pxl, colour);
			pxl.x++;
		}
		pxl.y++;
	}
	mlx_put_image_to_window(img->win.mlx, img->win.win, img->img, 0, 0);
	mlx_string_put(img->win.mlx, img->win.win, WIDTH - 80,
		20, WHITE, "[H] - Help");
}
