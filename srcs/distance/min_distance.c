/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 23:18:39 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"
#include "float.h"

static double	get_dist(t_ray *ray, t_obj *obj)
{
	static const t_dist_func func[] =
	{
		{sphere, &dist_sphere},
		{plane, &dist_plane},
		{cylinder, &dist_cylinder}
	};

	return (func[obj->type].dist_funct(ray, obj));
}

void	get_closest(t_obj *obj, t_ray *ray, t_payload *payload)
{
	int			i;
	double		new_dist;

	i = 0;
	payload->distance = DBL_MAX;
	while (obj && i < objs[i])
	{
		new_dist = get_dist(ray, &(objs[i]));
		if (new_dist < payload->distance)
		{
			payload->id = i;
			payload->distance = new_dist;
		}
		i++;
	}
	if (payload->distance != DBL_MAX)
	{
		payload->hitpoint = ray->origin + payload->distance * ray->direction;
		payload->hitnormal = get_normal(scene->obj, payload->hitpoint);
		payload->material = t_obj->material;
	}
}