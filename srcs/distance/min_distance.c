/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 10:38:47 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"
#include "float.h"

double	get_dist(t_ray *ray, t_obj *obj)
{
	static const t_dist_func func[] =
	{
		{sphere, &dist_sphere},
		{plane, &dist_plane},
		{cylinder, &dist_cylinder}
	};

	return (func[obj->type].dist_funct(ray, obj));
}

void	get_closest(t_scene *scene, t_ray *ray, t_payload *payload)
{
	int			i;
	double		new_dist;

	i = 0;
	payload->distance = DBL_MAX;
	while (scene->objs && i < scene->n_objs)
	{
		new_dist = get_dist(ray, &(scene->objs[i]));
		if (new_dist < payload->distance)
		{
			payload->obj_id = i;
			payload->distance = new_dist;
		}
		i++;
	}
	if (payload->distance != DBL_MAX)
	{
		payload->hitpoint = vec3_add(ray->origin, vec3_multf(ray->direction, payload->distance));
		payload->hitnorm = get_normal(&(scene->objs[i]), payload->hitpoint);
		payload->material = scene->objs[i].material;
	}
}