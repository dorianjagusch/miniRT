/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/28 20:58:26 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"
#include "float.h"

double	get_dist(t_ray *ray, t_obj *obj)
{
	static const t_dist_func	func[] = {
	{sphere, &dist_sphere},
	{plane, &dist_plane},
	{cylinder, &dist_cylinder},
	{disk, &dist_disk},
	};
	return (func[obj->type].dist_funct(ray, obj));
}

void	set_hitpoint(t_scene *scene, t_ray *ray, t_payload *payload)
{
	assert(!vec3_isnan(ray->origin));
	assert(!vec3_isnan(ray->direction));
	assert(!isnan(payload->distance));

	payload->hitpoint = vec3_add(ray->origin,
	vec3_multf(ray->direction, payload->distance));
	DEBUG_ONLY(printf("setting of hit point"));
	DEBUG_ONLY(print_vec3(payload->hitpoint, "set hitpoint"));
	assert(!vec3_isnan(payload->hitpoint));

	payload->point2cam = vec3_sub(payload->hitpoint, ray->origin);
	vec3_normalize(&payload->point2cam);
	assert(!vec3_isnan(payload->hitpoint));
	payload->hitnorm = get_normal(&(scene->objs[payload->obj_id]), payload->hitpoint);
	assert(!vec3_isnan(payload->hitnorm));
	payload->material = scene->objs[payload->obj_id].material;
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
}
