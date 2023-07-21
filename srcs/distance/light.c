/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/21 21:14:51 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"


static t_vec4	specular_colour(const t_scene *scene,
	const t_hitresult *hit, const t_light_info *light_info, int num)
{
	t_vec3	half_vec;
	float	spec_angle;
	t_vec4	colour;
	float	specular;
	
	half_vec = vec3_add(scene->directions[num], vec3_neg(scene->cam.dir));
	vec3_normalize(&half_vec);
	spec_angle = fmaxf(vec3_dot(hit->normal, half_vec), 0.0f);
	specular = powf(spec_angle, 100); // object specific
	colour = vec4_multf(vec4_multf(light_info->colour, specular * 100),
			1 / (scene->distances[num] * scene->distances[num]));
	return (colour);
}

t_light_info	light_distance(t_scene *scene, t_hitresult *hit)
{
	int				i;
	t_ray			shadowray;
	t_light_info	light_info;
	int				num;
	t_vec4			colour;

	num = 0;
	ft_bzero(&light_info, sizeof(t_light_info));
	shadowray.origin = hit->position;
	light_info.colour = (t_vec4){1, 0, 0, 0};
	colour = (t_vec4){1, 0, 0, 0};
	while (num < scene->n_lights)
	{
		i = 0;
		scene->directions[num] = vec3_sub(scene->lights[num].pos, hit->position);
		scene->distances[num] = vec3_mag(scene->directions[num]);
		vec3_normalize(&scene->directions[num]);
		shadowray.direction = scene->directions[num];
		while (i < scene->n_objs)
		{
			if (get_dist(&shadowray, &(scene->objs[i])) < scene->distances[num])
			{
				scene->distances[num] = 0;
				scene->directions[num] = (t_vec3) {0, 0, 0};
				i = 0;
				break ;
			}
			i++;
		}
		if (scene->distances[num] >= EPSILON)
		{
			light_info.intensity = fmax(vec3_dot(hit->normal, scene->directions[num])
				* scene->lights[num].ratio * 100, 0);
			assert(!isnan(light_info.intensity));
			colour = vec4_multf(vec4_multf(scene->lights[num].colour, light_info.intensity), 1 / (scene->distances[num] * scene->distances[num]));
			assert(!isnan(light_info.intensity));
			assert(!vec4_isnan(colour)); //
			light_info.colour = vec4_add(colour, light_info.colour);
			assert(!vec4_isnan(light_info.colour));
			scene->specular[num] = specular_colour(scene, hit, &light_info, num);
			assert(!vec4_isnan(scene->specular[num]));
		}
		num++;
	}
	return (light_info);
}
