/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 13:09:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_vec4	hit_shader(const t_ray *ray, const t_scene *scene,
		const t_hitresult *hit, const t_light_info *light_info)
{
	t_vec4	col[5];
	int		num;

	num = 0;
	ft_bzero(col, 5 * sizeof(t_vec4));
	col[ambient] = vec4_multf(scene->amb.colour, scene->amb.ratio);
	col[ambient] = vec4_compmult(hit->colour, col[ambient]);
	while (num < scene->n_lights)
	{
		if (scene->distances[num] >= EPSILON)
		{
			col[diffuse] = vec4_compmult(hit->colour,
					light_info->colour);
			assert(!vec4_isnan(col[diffuse]));
		}
		col[final] = vec4_add(col[diffuse], col[final]);
		num++;
	}
	col[final] = vec4_multf(col[final], 1.0f / scene->n_lights);
	col[final] = vec4_add_array(col[final], scene->specular, scene->n_lights);
	col[final] = vec4_add(col[ambient], col[final]);
	// if (ray->transparency < 1.0)
	// {
	// 	col[transparent] = vec4_multf(col[final], 1.0 - ray->transparency);
	// 	col[final] = vec4_add(vec4_multf(col[final], ray->transparency),
	// 			col[transparent]);
	// }
	return (col[final]);
}


