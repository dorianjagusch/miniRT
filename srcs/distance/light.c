/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 19:01:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"

t_light_info	light_distance(t_scene *scene, t_hitresult *hit)
{
	int				i;
	t_ray			shadowray;
	t_light_info	light_info;

	i = 0;
	shadowray.origin = hit->position;
	light_info.direction = vec3_sub(scene->light.pos, hit->position);
	light_info.distance = vec3_mag(light_info.direction);
	vec3_normalize(&light_info.direction);
	shadowray.direction = light_info.direction;
	while (i < scene->n_objs)
	{
		if (get_dist(&shadowray, &(scene->objs[i])) < light_info.distance)
		{
			print_light_info(light_info);
			light_info.distance = 0;
			light_info.intensity = 0;
			return (light_info);
		}
		i++;
	}
	light_info.intensity = fmax(vec3_dot(hit->normal, light_info.direction), 0);
	return (light_info);
}
