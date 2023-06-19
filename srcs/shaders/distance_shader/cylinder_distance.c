/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:14 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/19 23:50:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "scene.h"


static double dist_cylinder(t_ray *ray, t_obj *obj)
{

    t_vec3	c_dist;
	t_vec3	parameter;
	double discriminant;

	c_dist = ft_v3sub(ray->origin, obj->position);

	parameter.x = ray->direction.x * ray->direction.x +
		ray->direction.z * ray->direction.z;
	parameter.y = 2 * (c_dist.x * ray->direction.x +
		c_dist.z * ray->direction.z);
	parameter.z = c_dist.x * c_dist.x + c_dist.z * c_dist.z -
		obj->radius * obj->radius;

	discriminant = parameter.y * parameter.y -
		4 * parameter.x * parameter.z;

	if (discriminant < 0)
		return (DBL_MAX); // No intersection

	double t1 = (-parameter.y + sqrt(discriminant)) / (2 * parameter.x);
	double t2 = (-parameter.y - sqrt(discriminant)) / (2 * parameter.x);

	double y1 = ray->origin.y + ray->direction.y * t1;
	double y2 = ray->origin.y + ray->direction.y * t2;

	if (y1 >= obj->position.y && y1 <= obj->position.y + obj->height)
		return t1;
	else if (y2 >= obj->position.y && y2 <= obj->position.y + obj->height)
		return t2;
	else
		return -1;
}