/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 21:58:52 by djagusch         ###   ########.fr       */
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

void	get_closest(t_scene *scene, t_ray *ray, t_payload *payload)
{
	int			i;
	double		new_dist;
	t_payload	payload;

	i = 0;
	payload->distance = DBL_MAX;
	while (i < scene->n_objs)
	{
		new_dist = get_dist(ray, &(scene->objs[i]));
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
		payload->hitnormal = get_normal(obj, payload->hitpoint);
		payload->material = t_obj->material;
	}
	return (payload);

}