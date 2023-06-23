/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 10:38:47 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

double	dist_plane(t_ray *ray, t_obj *obj)
{
	double	p_dist;

	p_dist = vec3_dot(vec3_sub(obj->position, ray->origin), obj->normal);
	p_dist /= vec3_dot(ray->direction, obj->normal);
	if (p_dist > 0)
		return (p_dist);
	return (DBL_MIN);
}