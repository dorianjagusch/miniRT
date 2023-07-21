/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/21 14:16:26 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	reflect_ray(t_ray *ray, const t_hitresult *hit)
{
	t_ray	reflected_ray;

	reflected_ray.direction = vec3_neg(ray->direction);
	reflected_ray.direction = vec3_reflect(ray->direction, hit->normal);
	reflected_ray.origin = hit->position;
	return (reflected_ray);
}

t_vec4	trace_ray(t_ray *ray, t_scene *scene, int depth)
{
	t_hitresult		hit;
	t_light_info	light_info;
	t_vec4			colour;
	t_ray			reflected_ray;
	t_vec4			reflection;

	if (depth == BOUNCES)
		return ((t_vec4){1, 0, 0, 0});
	get_closest(scene, ray, &hit);
	if (hit.distance == FLT_MAX)
		return ((t_vec4){1, 0, 0, 0});
	assert(!isinf(hit.distance));
	set_hitpoint(scene, ray, &hit);
	assert(!vec3_isnan(hit.position)); //TODO: i was up to here when i did the light stuff
	light_info = light_distance(scene, &hit);
	colour = hit_shader(ray, scene, &hit, &light_info);
	reflected_ray = reflect_ray(ray, &hit);
	reflection = vec4_multf(trace_ray(&reflected_ray, scene, depth + 1), 0.9);
	colour = vec4_add(colour, reflection);
	vec4_clamp(&colour, 0.0, 1.0);
	return (colour);
}

int32_t	perpixel(t_img *img, t_vec2 pxl)
{
	t_ray			ray;
	t_vec4			colour;
	int				n_ray;

	colour = (t_vec4){1, 0, 0, 0};
	n_ray = 0;
	ray = create_primary_ray(&img->scene.cam, pxl);
	colour = vec4_add(colour, trace_ray(&ray, &img->scene, 0));
	vec4_clamp(&colour, 0, 1);
	return (vec4_toint32(colour));
}

static void	my_mlx_pixel_put(t_img *img, t_vec2 pxl, int colour)
{
	char		*dst;

	dst = img->addr + ((int)pxl.y * img->line_length
			+ (int)pxl.x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	render(t_img *img)
{
	t_vec2		pxl;
	int			colour;

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
	print_scene(img->scene);
}
