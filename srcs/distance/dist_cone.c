/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:28:17 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/20 13:24:18 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float cone_intersection(float delta, float a, float b)
{
	float intersect_1;
	float intersect_2;

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
	float	discriminant;
	float	intersection;
	t_vec3	oc;
	float	a;
	float 	b;
	float 	c;
    // Calculate the intersection between the ray and the cone
    oc = vec3_sub(ray->origin,  obj->cone.vertex);
    
	float cos_squared = cosf(obj->cone.angle) * cosf(obj->cone.angle); //?? yes but why
    a = vec3_dot(ray->direction, ray->direction) - (1.0f + cos_squared) * \
		vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(ray->direction, obj->cone.normal);
    b = 2.0f * (vec3_dot(ray->direction, oc) - (1.0f + cos_squared) * \
		vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
    c = vec3_dot(oc, oc) - (1.0f + cos_squared) * vec3_dot(oc, obj->cone.normal)\
	 * vec3_dot(oc, obj->cone.normal);
    discriminant = b * b - 4.0f * a * c;

	intersection = cone_intersection(discriminant, a, b);
    float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
    float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);

	if (t1 > t2)
	{
		float y2 = ray->origin.y + t1 * ray->direction.y;
		if (y2 > obj->cone.vertex.y && y2 < (obj->cone.vertex.y + obj->cone.height))
		{
			intersection = t2;
			return (intersection);
		}
	}
	if (t1 < t2)
	{
    	float y1 = ray->origin.y + t2 * ray->direction.y;
		if (y1 > obj->cone.vertex.y && y1 < (obj->cone.vertex.y + obj->cone.height))
		{
			intersection = t1;
			return (intersection);
		}
	}
		return (FLT_MAX);
}

float dist_cone(const t_ray *ray, t_object *obj)
{
    t_vec3	direction;
	float	discriminant;
	t_vec3	intersection_point;
	t_vec3	diff;
	float	check;
	float	t;

    direction = vec3_multf(obj->cone.normal, obj->cone.height);
    obj->cone.vertex = vec3_sub( obj->cone.pos, direction);
	t = get_intersect(ray, obj);
	if (t == FLT_MAX)
		return (FLT_MAX);
	intersection_point = vec3_add(ray->origin, vec3_multf(ray->direction, t));
	if (t > EPSILON)
	{
		diff = vec3_sub(intersection_point,  obj->cone.vertex);
		check =  vec3_dot(diff, obj->cone.normal);
		if (check < EPSILON)
			return (FLT_MAX);
		float height_squared = vec3_dot(diff, diff);
		float max_height_squared = obj->cone.height * obj->cone.height;
		if (height_squared < obj->cone.height)
			return (t);
	}
    return (FLT_MAX);
}
