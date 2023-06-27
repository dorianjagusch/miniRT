/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/26 17:19:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include <stdio.h>//

double	dist_plane(t_ray *ray, t_obj *obj)
{
	double	p_dist;

	// printf("------------\n");
	// printf("dist_plane\n");
	// printf("Origin: x: %f y: %f z: %f\n", ray->origin.x, ray->origin.y, ray->origin.z);
	// printf("Position: x: %f y: %f z: %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
	// printf("Normal: x: %f y: %f z: %f\n", obj->normal.x, obj->normal.y, obj->normal.z);
	p_dist = vec3_dot(vec3_sub(ray->origin, obj->position), obj->normal);
	p_dist /= vec3_dot(ray->direction, obj->normal);
	if (p_dist > 0)
		return (p_dist);
	return (DBL_MAX);
}
