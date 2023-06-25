/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:11:40 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/25 22:34:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "scene.h"
#include <float.h>

double	dist_cylinder(t_ray *ray, t_obj *obj)
{
	t_ray	rot_ray;
	t_vec3	params;
	t_vec2	res;
	double	discriminant;

	rot_ray.origin = vec3_rotate(ray->origin, obj->normal);
	rot_ray.direction = vec3_rotate(ray->direction, obj->normal);
	params.x = rot_ray.direction.x * rot_ray.direction.x + \
			rot_ray.direction.z * rot_ray.direction.z;
	params.y = 2.0 * (rot_ray.origin.x * rot_ray.direction.x + \
			rot_ray.origin.z * rot_ray.direction.z);
	params.z = rot_ray.origin.x * rot_ray.origin.x + \
			rot_ray.origin.z * rot_ray.origin.z - obj->radius * obj->radius;
	discriminant = params.y * params.y - 4.0 * params.x * params.z;
	if (discriminant < 0.0)
		return (DBL_MAX);
	res.x = (-params.y + sqrt(discriminant)) / (2.0 * params.x);
	res.y = (-params.y - sqrt(discriminant)) / (2.0 * params.x);
	if (res.x > 0.0 && fabs(rot_ray.origin.y + res.x * rot_ray.direction.y) \
			<= obj->height)
		return (res.x);
	if (res.y > 0.0 && fabs(rot_ray.origin.y + res.y * rot_ray.direction.y) \
			<= obj->height)
		return (res.y);
	return (DBL_MAX);
}
