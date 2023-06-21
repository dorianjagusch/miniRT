/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:49:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/21 22:18:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include <math.h>

double	dist_sphere(t_ray *ray, t_obj *obj)
{
	t_vec3	c_dist;
	t_vec3	parameter;
	double	discriminant;

	c_dist = ft_v3sub(ray->origin, obj->position);
	parameter.x = ft_v3dot(ray->direction, ray->direction);
	parameter.y = 2.0 * ft_v3dot(c_dist, ray->direction);
	parameter.z = ft_v3dot(c_dist,c_dist) - obj->radius * obj->radius;
	discriminant = parameter.y * parameter.y - 4 * parameter.x * parameter.z;
	if (discriminant < 0)
		return (DBL_MAX);
	return (-1.0 * (parameter.y * sqrt(discriminant) / (2.0 * parameter.x)));
}