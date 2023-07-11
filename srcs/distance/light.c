/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/11 14:00:27 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"

void	is_light_visible(const t_vec3 *cam_pos, const t_vec3 *light_pos,
	const t_vec3 *plane_pos, t_vec3 *normal)
{
	float	side1;
	float	side2;

	side1 = vec3_dot(vec3_sub(*cam_pos, *plane_pos), *normal);
	side2 = vec3_dot(vec3_sub(*light_pos, *plane_pos), *normal);
	if (side1 < 0 && side2 < 0)
		*normal = vec3_inv(*normal);
}

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
			DEBUG_ONLY(print_light_info(light_info));
			light_info.distance = 0;
			light_info.intensity = 0;
			return (light_info);
		}
		i++;
	}
	if (hit->type == plane_obj || hit->type == disk_obj)
		is_light_visible(&scene->cam.pos, &scene->light.pos,
			&hit->position, &hit->normal);
	light_info.intensity = fmax(vec3_dot(hit->normal, light_info.direction), 0);
	return (light_info);
}
