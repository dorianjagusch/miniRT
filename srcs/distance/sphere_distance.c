/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:49:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/26 01:22:16 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include <math.h>
#include <stdio.h>

double	dist_sphere(t_ray *ray, t_obj *obj)
{
	t_vec3	c_dist;
	t_vec3	parameter;
	double	discriminant;
	t_vec2	res;

	c_dist = vec3_sub(ray->origin, obj->position);
	parameter.x = vec3_dot(ray->direction, ray->direction);
	parameter.y = 2.0 * vec3_dot(c_dist, ray->direction);
	parameter.z = vec3_dot(c_dist, c_dist) - obj->radius * obj->radius;
	discriminant = parameter.y * parameter.y - 4 * parameter.x * parameter.z;
	if (discriminant < 0.0001)
		return (DBL_MAX);
	res.x = -parameter.y + sqrt(discriminant) / (2.0 * parameter.x);
	res.y = -parameter.y - sqrt(discriminant) / (2.0 * parameter.x);
	if (res.x > 0)
		return (res.x);
	if (res.y > 0)
		return (res.y);
	return (DBL_MAX);
}
