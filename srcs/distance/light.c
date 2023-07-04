/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/04 11:56:01 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_distance(t_scene *scene, t_payload *payload)
{
	//TODO: this currenty only handles one light was that something we needed changing??
	int		i;
	t_ray	hitray;

	i = 0;
	DEBUG_ONLY(print_vec3(payload->hitpoint, "hitpoint :"));
	assert(!vec3_isnan(payload->hitnorm));
	payload->hitpoint = vec3_add(payload->hitpoint,
			vec3_multf(payload->hitnorm, 1.0E-04)); //im not sure what this does or why it make such a big difference?
	assert(!vec3_isnan(payload->hitpoint));
	hitray.origin = payload->hitpoint;
	assert(!vec3_isnan(payload->hitpoint));
	DEBUG_ONLY(printf("\n----------------------\n"));
	DEBUG_ONLY(print_vec3(scene->light.pos, "light :"));
	DEBUG_ONLY(print_vec3(payload->hitpoint, "hitpoint :"));
	assert(!vec3_isnan(scene->light.pos));
	assert(!vec3_isnan(payload->hitpoint));
	payload->light_dir = vec3_sub(scene->light.pos, payload->hitpoint);
	payload->light_dist = vec3_mag(payload->light_dir);
	vec3_normalize(&(payload->light_dir));
	hitray.direction = payload->light_dir;
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
