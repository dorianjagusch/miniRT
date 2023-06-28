/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:18:48 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/28 21:31:10 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "scene.h"
#include "shaders.h"

double	dist_plane(t_ray *ray, t_obj *plane)
{
	double	denominator;
	t_vec3	oc;
	double	distance;

	denominator = vec3_dot(plane->normal, ray->direction);
	if (fabs(denominator) < 1.0E-08)
		return (DBL_MAX);
	distance = vec3_dot(vec3_sub(plane->position, ray->origin),
			plane->normal) / denominator;
	if (distance < 0)
		return (DBL_MAX);
	return (distance);
}
