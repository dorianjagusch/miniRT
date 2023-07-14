/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:04:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/13 14:41:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "minirt.h"

float	dist_disk(const t_ray *ray, t_object *obj)
{
	float	p_dist;
	t_vec3	hit_point;
	float	co;

	co = 0;
	p_dist = dist_plane(ray, obj);
	if (p_dist == FLT_MAX || p_dist < EPSILON)
		return (FLT_MAX);
	hit_point = vec3_add(ray->origin,
			vec3_multf(ray->direction, p_dist));
	co = vec3_dist(hit_point, obj->disk.pos);
	if (co > EPSILON && co <= obj->disk.radius)
		return (p_dist);
	return (FLT_MAX);
}
