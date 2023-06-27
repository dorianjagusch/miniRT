/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 13:42:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include <stdio.h>//

double	dist_plane(t_ray *ray, t_obj *obj)
{
	double	p_dist;
	double	angle;

	printf("------------\n");
	printf("Origin: x: %f y: %f z: %f\n", ray->origin.x, ray->origin.y, ray->origin.z);
	printf("Position: x: %f y: %f z: %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
	printf("Normal: x: %f y: %f z: %f\n", obj->normal.x, obj->normal.y, obj->normal.z);
	angle = vec3_dot(ray->direction, obj->normal);
	printf("angle: %f\n", angle);
	if (angle < 0.001)
		return (DBL_MAX);
	p_dist = vec3_dot(vec3_sub(ray->origin, obj->position), obj->normal);
	p_dist /= angle;
	if (p_dist > 0)
		return (p_dist);
	return (DBL_MAX);
}
