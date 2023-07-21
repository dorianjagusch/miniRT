/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:28:17 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/21 12:52:05 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	dist_caps(const t_ray *ray, const t_object *obj)
{
	float	dist;

	dist = dist_disk(ray, obj->cone.bottom);
	return (dist);
}

static void	check_height(const t_ray *ray, const t_cone *cone,
			float *dist)
{
	t_vec3	hitpoint;
	t_vec3	bottom_cap;
	float	cap_dist;

	bottom_cap = vec3_add(cone->vertex, vec3_multf(cone->normal,
				cone->height));
	hitpoint = vec3_add(ray->origin, vec3_multf(ray->direction, *dist));
	if (vec3_dot(cone->normal, vec3_sub(hitpoint, bottom_cap)) >= EPSILON
		|| vec3_dot(cone->normal, vec3_sub(hitpoint, cone->vertex)) <= EPSILON)
		*dist = FLT_MAX;
	
}

float	dist_cone(const t_ray *ray, t_object *obj)
{
	t_vec3	temp[2];
	t_vec3	params;
	float	discriminant;
	float	res[2];
	float	dist_cap;

	t_vec3	oc = vec3_sub(ray->origin,  obj->cone.vertex);
	//float cos_squared = cosf(obj->cone.angle) * cosf(obj->cone.angle);
	// params.x = vec3_dot(ray->direction, ray->direction) - (1.0f + cos_squared) * \
 	// 	vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(ray->direction, obj->cone.normal);
	// params.y = 2.0f * (vec3_dot(ray->direction, oc) - (1.0f + cos_squared) * \
 	// 	vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
	// params.z = vec3_dot(oc, oc) - (1.0f + cos_squared) * vec3_dot(oc, obj->cone.normal)\
 	//  * vec3_dot(oc, obj->cone.normal);
    params.x = vec3_dot(ray->direction, ray->direction) - (1 + obj->cone.radius * obj->cone.radius / (obj->cone.height * obj->cone.height)) * pow(vec3_dot(ray->direction, obj->cone.normal), 2);
    params.y = 2 * (vec3_dot(ray->direction, oc) - (1 + obj->cone.radius * obj->cone.radius / (obj->cone.height * obj->cone.height)) * vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
    params.z = vec3_dot(oc, oc) - (1 + obj->cone.radius * obj->cone.radius / (obj->cone.height * obj->cone.height)) * pow(vec3_dot(oc, obj->cone.normal), 2);
	discriminant = params.y * params.y - 4 * params.x * params.z;
	if (discriminant < EPSILON)
		return (FLT_MAX);
	res[0] = (-params.y - sqrt(discriminant)) / (2 * params.x);
	res[1] = (-params.y + sqrt(discriminant)) / (2 * params.x);
	if (res[0] > EPSILON)
		check_height(ray, &(obj->cone), &(res[0]));
	if (res[1] > EPSILON)
		check_height(ray, &(obj->cone), &(res[1]));
	dist_cap = dist_caps(ray, obj);
	res[0] = which_pos_min(res[0], res[1], dist_cap);
	if (isnan(res[0]) == 0 && res[0] == dist_cap && res[0] != FLT_MAX)
		obj->cone.disk_hit = 1;
	return (res[0]);
}


