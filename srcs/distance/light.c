/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 17:45:03 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_distance(t_scene *scene, t_payload *payload)
{
	//TODO: this currenty only handles one light?
	int		i;
	t_ray	hitray;

	i = 0;
	hitray.origin = payload->hitpoint;
	hitray.direction = payload->hitnorm;
	DEBUG_ONLY(printf("\n----------------------\n"));
	DEBUG_ONLY(print_vec3(scene->light.pos, "light :"));
	DEBUG_ONLY(print_vec3(payload->hitpoint, "hitpoint :"));
	payload->light_dir = vec3_sub(scene->light.pos, payload->hitpoint);
	payload->light_dist = vec3_mag(payload->light_dir);
	vec3_normalize(&(payload->light_dir));
	assert(!vec3_isnan(payload->light_dir));
	while (i < scene->n_objs)
	{
		if (get_dist(&hitray, &(scene->objs[i])) < payload->light_dist)
		{
			payload->light_dist = 0;
			return ;
		}
		i++;
	}
	DEBUG_ONLY(printf("\n----------------------\n"));
}
