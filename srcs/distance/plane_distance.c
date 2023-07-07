/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/06 00:33:59 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"

double	dist_plane(const t_ray *ray, const t_object *obj)
{
	double	denominator;
	double	signed_dist;
	double	p_dist;

	denominator = vec3_dot(ray->direction, obj->plane.normal);
	signed_dist = vec3_dot(obj->plane.normal, ray->origin) + obj->plane.d;
	if (denominator > EPSILON && signed_dist > EPSILON)
		return (DBL_MAX);
	if (denominator < EPSILON && signed_dist <= EPSILON)
		return (DBL_MAX);
	p_dist = (-obj->plane.d - vec3_dot(ray->origin, obj->plane.normal)) \
		/ denominator;
	if (p_dist >= EPSILON)
		return (p_dist);
	return (DBL_MAX);
}
