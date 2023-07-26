/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:19:07 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "float.h"

float	get_dist(const t_ray *ray, t_object *obj)
{
	static const t_dist_function	func[] = {
		dist_sphere,
		dist_plane,
		dist_cylinder,
		dist_disk,
	};

	return (func[obj->type](ray, obj));
}

void	get_closest(const t_scene *scene, const t_ray *ray, t_hitresult *hit)
{
	int			i;
	float		new_dist;

	i = 0;
	new_dist = 0;
	hit->distance = FLT_MAX;
	while (scene->objs && i < scene->n_objs)
	{
		new_dist = get_dist(ray, &(scene->objs[i]));
		if (new_dist < hit->distance)
		{
			hit->obj_id = i;
			hit->distance = new_dist;
		}
		i++;
	}
}
