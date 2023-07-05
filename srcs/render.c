/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 13:49:41 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reflect_ray(t_ray *ray, const t_hitresult *hit)
{
		ray->direction = vec3_neg(ray->direction);
		ray->direction = vec3_reflect(ray->direction, hit->normal);
		ray->origin = hit->position;
}

t_vec4	trace_ray(t_ray *ray, t_scene *scene, int depth)
{
	t_hitresult		hit;
	t_light_info	light_info;
	t_vec4			colour;

	if (depth >= BOUNCES)
		return ((t_vec4){1, 0, 0, 0});
	get_closest(scene, ray, &hit);
	if (hit.distance == DBL_MAX)
		return ((t_vec4){1, 0, 0, 0});
	set_hitpoint(scene, ray, &hit);
	light_info = light_distance(scene, &hit);
	colour = hit_shader(ray, scene, &hit, &light_info);
	reflect_ray(ray, &hit);
	vec4_clamp(&colour, 0.0, 1.0);
	return (colour);
}

int32_t	perpixel(t_img *img, t_vec2 pxl)
{
	t_ray			ray;
	t_vec4			colour;
	int				i;

	i = 0;
	colour = (t_vec4){1, 0, 0, 0};
	ray = create_primary_ray(&img->scene.cam, pxl);
	colour = trace_ray(&ray, &img->scene, 0);
	vec4_clamp(&colour, 0, 1);
	return (vec4_toint32(colour));
}

static void	my_mlx_pixel_put(t_img *img, t_vec2 pxl, int colour)
{
	char		*dst;

	DEBUG_ONLY(printf("1st debug print color: %d\n", colour));

	dst = img->addr + ((int)pxl.y * img->line_length
			+ (int)pxl.x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
	DEBUG_ONLY(printf("debug print color: %d\n", colour));
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
