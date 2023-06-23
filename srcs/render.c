/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 11:38:42 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	miss(t_img *img)
{
	return (img->scene.amb.colour);
}

//set loop in per pixel function for bounces and modify ray in hitshader 
//or call relect function
// and reassign ray while saving the colour
int32_t	perpixel(t_img *img, t_vec2 pxl)
{
	t_ray		ray;
	t_payload	payload;
	t_vec4		colour;
	int			i;

	i = 0;
	ray = create_primary_ray(&img->scene.cam, pxl);//
	while (i < BOUNCES)
	{
		get_closest(&(img->scene), &ray, &payload);
		if (payload.distance == DBL_MAX)
		{
			colour = vec4_add(colour, miss(img));
			break;
		}
		colour = vec4_add(colour, hit_shader(&(img->scene), &payload));
		ray.direction = vec3_multf(ray.direction, -1),
		ray.direction = vec3_reflect(ray.direction, payload.hitnorm);
		ray.origin = vec3_add(payload.hitpoint, vec3_multf(payload.hitnorm, 0.0001));
		i++;
	}
	vec4_clamp(&colour, 0, 1);
	return (vec4_toint32(colour));
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
