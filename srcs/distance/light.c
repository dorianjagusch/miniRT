/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 22:45:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double light_dist(t_scene scene, t_payload *payload)
{
	int		i;
	t_ray	hitray;

	i = 0;
	payload->light_dir = ft_v3sub(scene->light, payload.hitpoint);
	payload->light_dist = ft_v3mag(payload->light_dir);
	hitray = (t_ray){payload.hitpoint, payload.normal};
	while (scene.obj[i])
	{
		if (get_distance(scene.objs[i], hitray) < light_dist)
			return(-1);
		i++;
	}
	ft_v3norm(payload->light_dir);
	return (light_dist);
}