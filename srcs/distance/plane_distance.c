/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/28 16:08:25 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"

double    dist_plane(t_ray *ray, t_obj *obj)
{
	double	denominator;
	t_vec3	oc;
	double	distance;

	denominator = vec3_dot(plane->normal, ray->direction);
	if (fabs(denominator) < 1.0E-08)
		return (DBL_MAX);
	distance = vec3_dot(vec3_sub(plane->position, ray->origin),
			plane->normal) / denominator;
	if (distance < 0)
		return (DBL_MAX);
	return (distance);
	double denominator;
    double signed_dist;
    double p_dist; //t

	denominator = vec3_dot(ray->direction, obj->normal);
    signed_dist = vec3_dot(obj->normal, ray->origin) + obj->d;
    if (denominator > EPSILON && signed_dist > EPSILON)
        return (DBL_MAX);
    if (denominator <  EPSILON && signed_dist <= EPSILON)
        return (DBL_MAX);

    p_dist = (-obj->d - vec3_dot(ray->origin, obj->normal)) / denominator;
    if (p_dist >= 0.0)
        return (p_dist);

    return (DBL_MAX);
}
