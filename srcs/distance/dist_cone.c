/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:28:17 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/20 11:32:29 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float cone_intersection(float delta, float a, float b)
// {
// 	float intersect_1;
// 	float intersect_2;

// 	// intersect_1 = (-b + sqrt(delta)) / (2 * a);
// 	// intersect_2 =(-b - sqrt(delta)) / (2 * a);

// 	intersect_1 = (-b - sqrt(delta)) / (2 * a);
// 	intersect_2 = (-b + sqrt(delta)) / (2 * a);
// 	if (intersect_2 > EPSILON && intersect_1 > intersect_2)
// 		return (intersect_2);
// 	else if (intersect_1 > EPSILON)
// 		return (intersect_1);
// 	return (FLT_MAX);
// }
// static float get_intersect(const t_ray *ray, t_object *obj)
// {
//     t_vec3 oc = vec3_sub(ray->origin, obj->cone.vertex);
//     float cos_squared = cosf(obj->cone.angle) * cosf(obj->cone.angle);
//     float a = vec3_dot(ray->direction, ray->direction) - (1.0f + cos_squared) *
//               vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(ray->direction, obj->cone.normal);
//     float b = 2.0f * (vec3_dot(ray->direction, oc) - (1.0f + cos_squared) *
//                       vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
//     float c = vec3_dot(oc, oc) - (1.0f + cos_squared) * vec3_dot(oc, obj->cone.normal) *
//               vec3_dot(oc, obj->cone.normal);
//     float discriminant = b * b - 4.0f * a * c;
//     float intersection = FLT_MAX;

//     if (discriminant > EPSILON)
//     {
//         float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
//         float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);
//         float y1 = ray->origin.y + t1 * ray->direction.y;
//         float y2 = ray->origin.y + t2 * ray->direction.y;

//         if (y1 > obj->cone.vertex.y && y1 < (obj->cone.vertex.y + obj->cone.height))
//             intersection = t1;
//         else if (y2 > obj->cone.vertex.y && y2 < (obj->cone.vertex.y + obj->cone.height))
//             intersection = t2;
//     }

//     return intersection;
// }

// static float get_intersect(const t_ray *ray, t_object *obj)
// {
// 	float discriminant;
	
//     // Calculate the intersection between the ray and the cone
//     t_vec3 oc = vec3_sub(ray->origin,  obj->cone.vertex); // Vector from the vertex to the ray origin
//     float cos_squared = cosf(obj->cone.angle) * cosf(obj->cone.angle); // Square of the cosine of the cone angle
//     float a = vec3_dot(ray->direction, ray->direction) - (1.0f + cos_squared) * \
// 		vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(ray->direction, obj->cone.normal);
//     float b = 2.0f * (vec3_dot(ray->direction, oc) - (1.0f + cos_squared) * \
// 		vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
//     float c = vec3_dot(oc, oc) - (1.0f + cos_squared) * vec3_dot(oc, obj->cone.normal)\
// 	 * vec3_dot(oc, obj->cone.normal);
//     discriminant = b * b - 4.0f * a * c;
// 	float intersection = cone_intersection(discriminant, a, b);
// 	obj->cone.intersect_y = oc.y + intersection * ray->direction.y;
// 	return (intersection);
// }

// float dist_cone(const t_ray *ray, t_object *obj)
// {
//     t_vec3	direction;
// 	float	discriminant;
// 	t_vec3	intersection_point;

//     direction = vec3_multf(obj->cone.normal, obj->cone.height);
//     obj->cone.vertex = vec3_sub( obj->cone.pos, direction);
// 	float t = get_intersect(ray, obj);
// 	if (t == FLT_MAX)
// 		return (FLT_MAX);
// 	intersection_point = vec3_add(ray->origin, vec3_multf(ray->direction, t));
// 	if (t > EPSILON)
// 	{
// 		t_vec3 diff = vec3_sub(intersection_point,  obj->cone.vertex);
// 		float check =  vec3_dot(diff, obj->cone.normal);
// 		if (check < EPSILON)
// 			return (FLT_MAX);
// 		float height_squared = vec3_dot(diff, diff);
// 		float max_height_squared = obj->cone.height * obj->cone.height;
// 		if (height_squared < obj->cone.height)
// 			return (t);
// 	}
//     return (FLT_MAX);
// }

float cone_intersection(float delta, float a, float b)
{
    float intersect_1;
    float intersect_2;

    if (a == 0.0)
        return 0;
    intersect_1 = (-b - sqrt(delta)) / (2 * a);
    intersect_2 = (-b + sqrt(delta)) / (2 * a);
    if (intersect_1 > intersect_2)
        return intersect_2;
    else
        return intersect_1;
}


float dist_cone(const t_ray *ray, t_object *cone)
{
	float posdiff_x;
	float posdiff_z;
	float height_diff;
	float qudratics[3]; // a = 0, b = 1, c = 2
	float intersect;
	float intersect_y;
	float delta;

	t_vec3 translated_origin = vec3_sub(ray->origin, cone->cone.pos);
	posdiff_x = translated_origin.x - cone->cone.vertex.x;
	posdiff_z = translated_origin.z - cone->cone.vertex.z;
	height_diff = cone->cone.height - translated_origin.y;
	qudratics[0] = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z) - (cone->cone.angle * (ray->direction.y * ray->direction.y));
	qudratics[1] = (2 * posdiff_x * ray->direction.x) + (2 * posdiff_z * ray->direction.z) + (2 * cone->cone.angle * height_diff * ray->direction.y);
	qudratics[2] = (posdiff_x * posdiff_x) + (posdiff_z * posdiff_z) - (cone->cone.angle * (height_diff * height_diff));
	delta = qudratics[1] * qudratics[1] - 4 * (qudratics[0] * qudratics[2]);
	cone->cone.disk_hit = dist_disk(ray, cone->cone.bottom);
	intersect = cone_intersection(delta, qudratics[0], qudratics[1]);
	intersect_y = translated_origin.y + intersect * ray->direction.y;
	if (intersect >= cone->cone.disk_hit && intersect_y >= 0 && intersect_y <= cone->cone.height)
	{
		intersect = cone->cone.height - intersect_y;
		return (intersect);
	}
	else if (cone->cone.disk_hit > EPSILON)
	{
		intersect = cone->cone.height - (cone->cone.height - intersect_y);
		return (intersect);
	}
	return (FLT_MAX);
}