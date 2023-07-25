/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:42 by djagusch          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/25 16:57:41 by djagusch         ###   ########.fr       */
=======
/*   Updated: 2023/07/25 16:56:01 by smorphet         ###   ########.fr       */
>>>>>>> f2f1fc9e24b7421aab88e94c4f2d4c5b343cf962
/*                                                                            */
/* ************************************************************************** */

#include "patterns_bonus.h"

#ifndef EPSILON
# define EPSILON 10e-8
#endif

t_vec2	cylinder_map(t_vec3 *point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	offset;
	t_vec3	projection;
	t_vec3	axis[2];
	float	angle;

	if (obj->cylinder.disk_hit == 1)
		return (disk_map(point, obj->cylinder.bottom));
	if (obj->cylinder.disk_hit == 2)
		return (disk_map(point, obj->cylinder.top));
	offset = vec3_sub(*point, obj->cylinder.pos);
	axis[U] = vec3_cross((t_vec3){EPSILON, 1, EPSILON}, obj->cylinder.normal);
	vec3_normalize(&(axis[U]));
	axis[V] = vec3_cross(obj->cylinder.normal, axis[U]);
	projection.x = vec3_dot(offset, axis[U]);
	projection.y = vec3_dot(offset, axis[V]);
	projection.z = vec3_dot(offset, obj->cylinder.normal);
	angle = atan2(projection.y, projection.x);
	if (angle < 0.0)
		angle += 2.0f * M_PI;
	uv.x = angle * M_1_DIV_2PI;
	uv.y = (projection.z + obj->cylinder.height / 2.0f) / obj->cylinder.height;
	return (uv);
}
