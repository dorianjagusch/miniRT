/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 16:24:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"

double	dist_plane(t_ray *ray, t_obj *obj)
{
	double	denominator;
	double	signed_dist;
	double	p_dist;

	denominator = vec3_dot(ray->direction, obj->normal);
	signed_dist = vec3_dot(obj->normal, ray->origin) + obj->d;
	if (denominator > EPSILON && signed_dist > EPSILON)
		return (DBL_MAX);
	if (denominator < EPSILON && signed_dist <= EPSILON)
		return (DBL_MAX);
	p_dist = (-obj->d - vec3_dot(ray->origin, obj->normal)) / denominator;
	if (p_dist >= 0.0)
		return (p_dist);
	return (DBL_MAX);
}
