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
	t_vec3	temp;
	
	printf("------------\n");
	printf("Origin: x: %f y: %f z: %f\n", ray->origin.x, ray->origin.y, ray->origin.z);
	printf("Position: x: %f y: %f z: %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
	printf("Normal: x: %f y: %f z: %f\n", obj->normal.x, obj->normal.y, obj->normal.z);
	vec3_normalize(&obj->normal);
	angle = vec3_dot(obj->normal, ray->direction);
	printf("angle: %f\n", angle);
	if (angle < 0.001)
		return (DBL_MAX);
	temp = vec3_sub(ray->origin, obj->position); //here is fucked
	p_dist /= angle;
	printf("p_dist = \n", p_dist);
	if (p_dist > 0)
		return (p_dist);
	return (DBL_MAX);
}
