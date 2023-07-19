/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:28:17 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/19 17:01:41 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float cone_intersection(float delta, float a, float b)
{
	float intersect_1;
	float intersect_2;

	// intersect_1 = (-b + sqrt(delta)) / (2 * a);
	// intersect_2 =(-b - sqrt(delta)) / (2 * a);

	intersect_1 = (-b - sqrt(delta)) / (2 * a);
	intersect_2 = (-b + sqrt(delta)) / (2 * a);
	if (intersect_2 > EPSILON && intersect_1 > intersect_2)
		return (intersect_2);
	else if (intersect_1 > EPSILON)
		return (intersect_1);
	return (FLT_MAX);
}

static float get_intersect(const t_ray *ray, t_object *obj)
{
	float discriminant;
	
    // Calculate the intersection between the ray and the cone
    t_vec3 oc = vec3_sub(ray->origin,  obj->cone.vertex); // Vector from the vertex to the ray origin
    float cos_squared = cosf(obj->cone.angle) * cosf(obj->cone.angle); // Square of the cosine of the cone angle
    float a = vec3_dot(ray->direction, ray->direction) - (1.0f + cos_squared) * \
		vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(ray->direction, obj->cone.normal);
    float b = 2.0f * (vec3_dot(ray->direction, oc) - (1.0f + cos_squared) * \
		vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
    float c = vec3_dot(oc, oc) - (1.0f + cos_squared) * vec3_dot(oc, obj->cone.normal)\
	 * vec3_dot(oc, obj->cone.normal);
    discriminant = b * b - 4.0f * a * c;
	float intersection = cone_intersection(discriminant, a, b);
	obj->cone.intersect_y = oc.y + intersection * ray->direction.y;
	return (intersection);
}

float dist_cone(const t_ray *ray, t_object *obj)
{
    t_vec3	direction;
	float	discriminant;
	t_vec3	intersection_point;

    direction = vec3_multf(obj->cone.normal, obj->cone.height);
    obj->cone.vertex = vec3_sub( obj->cone.pos, direction);
	float t = get_intersect(ray, obj);
	if (t == FLT_MAX)
		return (FLT_MAX);
	intersection_point = vec3_add(ray->origin, vec3_multf(ray->direction, t));
	if (t > EPSILON)
	{
		t_vec3 diff = vec3_sub(intersection_point,  obj->cone.vertex);
		float check =  vec3_dot(diff, obj->cone.normal);
		if (check < EPSILON)
			return (FLT_MAX);
		float height_squared = vec3_dot(diff, diff);
		float max_height_squared = obj->cone.height * obj->cone.height;
		if (height_squared < obj->cone.height)
			return (t);
	}
    return (FLT_MAX);
}