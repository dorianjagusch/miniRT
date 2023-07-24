/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 14:09:48 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"


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
