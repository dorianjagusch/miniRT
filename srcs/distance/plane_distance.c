/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 18:00:33 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"

float	dist_plane(const t_ray *ray, t_object *obj)
{
	float	denominator;
	float	signed_dist;
	float	p_dist;

	denominator = vec3_dot(ray->direction, obj->plane.normal);
	signed_dist = vec3_dot(obj->plane.normal, ray->origin) + obj->plane.d;
	if (denominator > EPSILON && signed_dist > EPSILON)
		return (FLT_MAX);
	if (denominator < EPSILON && signed_dist <= EPSILON)
		return (FLT_MAX);
	p_dist = (-obj->plane.d - vec3_dot(ray->origin, obj->plane.normal)) \
		/ denominator;
	if (p_dist >= EPSILON)
		return (p_dist);
	return (FLT_MAX);
}
