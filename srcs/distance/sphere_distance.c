/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:49:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 11:37:34 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include <math.h>

double	dist_sphere(t_ray *ray, t_obj *obj)
{
	t_vec3	c_dist;
	t_vec3	parameter;
	double	discriminant;

	c_dist = vec3_sub(ray->origin, obj->position);
	parameter.x = vec3_dot(ray->direction, ray->direction);
	parameter.y = 2.0 * vec3_dot(c_dist, ray->direction);
	parameter.z = vec3_dot(c_dist,c_dist) - obj->radius * obj->radius;
	discriminant = parameter.y * parameter.y - 4 * parameter.x * parameter.z;
	if (discriminant < 0)
		return (DBL_MAX);
	return (-1.0 * (parameter.y * sqrt(discriminant) / (2.0 * parameter.x)));
}
