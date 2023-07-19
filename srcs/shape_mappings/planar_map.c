/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planar_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:48:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/19 17:34:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"
#include <float.h>

#ifndef EPSILON
# define EPSILON 1e-8
#endif

t_vec2	plane_map(t_vec3 *point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	axis[2];

	axis[U] = vec3_cross(obj->plane.normal, (t_vec3){(float)INT_MAX,
			(float)INT_MAX, (float)INT_MAX});
	vec3_normalize(&axis[U]);
	axis[V] = vec3_cross(axis[U], obj->plane.normal);
	uv.x = vec3_dot(*point, axis[U]);
	uv.y = vec3_dot(*point, axis[V]);
	return (uv);
}

t_vec2	disk_map(t_vec3 *point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	point_t;
	float	angle;

	point_t = vec3_sub(*point, obj->disk.pos);
	angle = atan2(point_t.z, point_t.x);
	if (angle < 0.0)
		angle += 2.0 * M_PI;
	uv.x = angle * M_1_DIV_2PI;
	uv.y = vec3_mag(point_t) / obj->disk.radius;
	return (uv);
	return (uv);
}
