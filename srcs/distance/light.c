/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/26 22:55:43 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_distance(t_scene *scene, t_payload *payload)
{
	int		i;
	t_ray	hitray;

	i = 0;
	payload->light_dir = vec3_sub(scene->light.pos, payload->hitpoint);
	payload->light_dist = vec3_mag(payload->light_dir);
	payload->hitpoint = vec3_add(payload->hitpoint,
			vec3_multf(payload->hitnorm, 0.0001));
	hitray.origin = payload->hitpoint;
	hitray.direction = payload->hitnorm;
	while (i < scene->n_objs)
	{
		if (get_dist(&hitray, &(scene->objs[i])) < payload->light_dist)
		{
			payload->light_dist = -1;
			return ;
		}
		i++;
	}
	printf("light_dist: %f\n", payload->light_dist);
	vec3_normalize(&(payload->light_dir));
}
