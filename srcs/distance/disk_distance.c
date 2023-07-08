/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:04:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 18:00:15 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

float	dist_disk(const t_ray *ray, t_object *obj)
{
	float	p_dist;
	t_vec3	intersection_point;
	float	distance_to_center;

	distance_to_center = 0;
	p_dist = dist_plane(ray, obj);
	if (p_dist == FLT_MAX)
		return (p_dist);
	intersection_point = vec3_add(ray->origin,
			vec3_multf(ray->direction, p_dist));
	distance_to_center = vec3_dist(intersection_point, obj->disk.pos);
	if (distance_to_center <= obj->disk.radius)
		return (p_dist);
	return (FLT_MAX);
}
