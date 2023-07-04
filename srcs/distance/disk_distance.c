/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:04:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/04 12:05:25 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

double	dist_disk(t_ray *ray, t_obj *obj)
{
	double	p_dist;
	t_vec3	intersection_point;
	double	distance_to_center;

	distance_to_center = 0;
	p_dist = dist_plane(ray, obj);
	if (p_dist == DBL_MAX)
		return (p_dist);
	intersection_point = vec3_add(ray->origin,
			vec3_multf(ray->direction, p_dist));
	distance_to_center = vec3_dist(intersection_point, obj->pos);
	if (distance_to_center <= obj->radius)
		return (p_dist);
	return (DBL_MAX);
}
