/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/26 23:49:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	miss(t_img *img)
{
	return (img->scene.amb.colour);
}


// t_vec4	draw_circle(t_vec2 pxl)
// {
// 	t_vec2 center = (t_vec2){WIDTH / 2,  HEIGHT / 2};
// 	int		radius = 50;

// 	int x_coord = (pxl.x - center.x);
// 	int y_coord = (pxl.y - center.y);
// 	if (x_coord * x_coord + y_coord * y_coord < radius * radius)
// 		return ((t_vec4){1, 0.56789876855, 1, 1});
// 	return ((t_vec4){1, 0, .78987, 0});
// }
//set loop in per pixel function for bounces and modify ray in hitshader
//or call relect function
// and reassign ray while saving the colour
int32_t	perpixel(t_img *img, t_vec2 pxl)
{
	t_ray		ray;
	t_payload	payload;
	t_vec4		colour;
	t_vec4		norm_colour;
	int			i;

	i = 0;
	colour = (t_vec4){1, 0, 0, 0};
	ray = create_primary_ray(&img->scene.cam, pxl);
	while (i < BOUNCES)
	{
		get_closest(&(img->scene), &ray, &payload);
		if (payload.distance == DBL_MAX)
		{
			colour = vec4_propadd(miss(img), colour, img->scene.amb.ratio);
			break ;
		}
		//colour = (t_vec4){1, payload.hitnorm.x + 0.5, payload.hitnorm.y + 0.5, payload.hitnorm.z + 0.5};
		colour = vec4_add(colour, hit_shader(&(img->scene), &payload));
		//printf("shaded colour:\nr:%f g:%f, b:%f\n", colour.x, colour.y, colour.z);
		// ray.direction = vec3_multf(ray.direction, -1),
		// ray.direction = vec3_reflect(ray.direction, payload.hitnorm);
		// ray.origin = vec3_add(payload.hitpoint, vec3_multf(payload.hitnorm, 0.0001));
		i++;
	}
	//colour = draw_circle(pxl);
	vec4_clamp(&colour, 0, 1);
	return (vec4_toint32(colour));
}

static void	my_mlx_pixel_put(t_img *img, t_vec2 pxl, int colour)
{
	char	*dst;

	dst = img->addr + ((int)pxl.y * img->line_length
			+ (int)pxl.x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	render(t_img *img)
{
	t_vec2		pxl;
	int			tot_res;
	u_int32_t	colour;

	tot_res = HEIGHT * WIDTH;
	pxl.y = 0;
	print_objs(img->scene.objs[0]);
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
