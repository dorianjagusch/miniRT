/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/14 16:05:02 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"

// float	dist_plane(const t_ray *ray, t_object *obj)
// {
// 	float	denominator;
// 	float	signed_dist;
// 	float	p_dist;

// 	denominator = vec3_dot(ray->direction, obj->plane.normal);
// 	signed_dist = vec3_dot(obj->plane.normal, ray->origin) + obj->plane.d;
// 	if (denominator > EPSILON && signed_dist > EPSILON)
// 		return (FLT_MAX);
// 	if (denominator < EPSILON && signed_dist <= EPSILON)
// 		return (FLT_MAX);
// 	p_dist = (-obj->plane.d - vec3_dot(ray->origin, obj->plane.normal)) \
// 		/ denominator;
// 	if (p_dist >= EPSILON)
// 		return (p_dist);
// 	return (FLT_MAX);
// }

float	dist_plane(const t_ray *ray, t_object *obj)
{
	float	denominator;
	t_vec3	oc;
	float	distance;

	denominator = vec3_dot(obj->plane.normal, ray->direction);
	if (fabs(denominator) < EPSILON)
		return (FLT_MAX);
	distance = vec3_dot(vec3_sub(obj->plane.pos, ray->origin),
			obj->plane.normal) / denominator;
	if (distance < EPSILON)
		return (FLT_MAX);
	return (distance);
}
