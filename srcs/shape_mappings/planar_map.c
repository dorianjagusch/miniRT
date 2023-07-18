/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planar_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:48:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/18 09:55:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"

#ifndef EPSILON
# define EPSILON 1e-8
#endif

t_vec2	plane_map(t_vec3 *point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	axis[2];

	axis[U] = vec3_cross(obj->plane.normal, (t_vec3){EPSILON, 1, EPSILON});
	vec3_normalize(&axis[U]);
	axis[V] = vec3_cross(axis[U], obj->plane.normal);
	uv.x = fabsf(vec3_dot(vec3_sub(*point, obj->plane.pos), axis[U]));
	uv.y = fabsf(vec3_dot(vec3_sub(*point, obj->plane.pos), axis[V]));
	return (uv);
}
