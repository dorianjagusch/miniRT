/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/16 15:47:43 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"

// int	is_light_visible(const t_vec3 *cam_pos, const t_vec3 *light_pos,
// 	const t_vec3 *plane_pos, t_vec3 *normal)
// {
// 	float	side1;
// 	float	side2;
// 	t_vec3	normal_light;

// 	side1 = vec3_dot(vec3_sub(*cam_pos, *plane_pos), *normal);
// 	normal_light = vec3_sub(*light_pos, *plane_pos);
// 	side2 = vec3_dot(normal_light, *normal);
// 	if ((side1 < 0 && side2 < 0) || (side1 > 0 && side2 > 0))
// 	{
// 		if (side1 < 0 && side2 < 0)
// 			*normal = vec3_neg(*normal);
// 		return (1);
// 	}
// 	if (side1 < 0)
// 	{
// 		*normal = vec3_neg(*normal);
// 		return (1);
// 	}
// 	return (0);
// }

t_light_info	light_distance(t_scene *scene, t_hitresult *hit)
{
	int				i;
	t_ray			shadowray;
	t_light_info	light_info;

	i = 0;
	
	DEBUG_ONLY(print_vec3(hit->position, "hit position"));
	shadowray.origin = hit->position;
	DEBUG_ONLY(print_vec3(shadowray.origin, "shadow ray"));
	light_info.direction = vec3_sub(scene->light.pos, hit->position);
	DEBUG_ONLY(print_vec3(light_info.direction, "light info dir"));
	light_info.distance = vec3_mag(light_info.direction);
	DEBUG_ONLY(print_vec3(light_info.direction, "light info dir"));
	vec3_normalize(&light_info.direction);
	DEBUG_ONLY(print_vec3(light_info.direction, "light info dir"));
	shadowray.direction = light_info.direction;
	while (i < scene->n_objs)
	{
		if (get_dist(&shadowray, &(scene->objs[i])) < light_info.distance)
		{
			light_info.distance = 0;
			light_info.intensity = 0;
			return (light_info);
		}
		i++;
	}
	light_info.intensity = fmax(vec3_dot(hit->normal, light_info.direction) \
		* scene->light.ratio * 100, 0);
	light_info.colour = scene->light.colour;
	return (light_info);
}
