/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:28:17 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/19 22:38:25 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


//////////////////////////the dist cylinder, needs the helper functions/////////////////////////////////////
// float dist_cone(const t_ray *ray, t_object *obj)
// {
//     t_vec3 temp[2];
//     t_vec3 params;
//     float discriminant;
//     float res[2];
//     float dist_cap;

//     calc_temps(ray, &(obj->cone), temp);
//     params.x = vec3_dot(temp[0], temp[0]) - (1 + obj->cone.angle * obj->cone.angle)
//                                           * vec3_dot(temp[1], temp[1]);
//     params.y = 2 * (vec3_dot(temp[0], temp[0]) - (1 + obj->cone.angle * obj->cone.angle)
//                                                * vec3_dot(ray->origin, temp[1]));
//     params.z = vec3_dot(temp[0], temp[0]) - (1 + obj->cone.angle * obj->cone.angle)
//                                           * vec3_dot(ray->origin, ray->origin);
//     discriminant = params.y * params.y - 4 * params.x * params.z;
//     if (discriminant < EPSILON)
//         return FLT_MAX;
//     res[0] = (-params.y - sqrtf(discriminant)) / (2 * params.x);
//     res[1] = (-params.y + sqrtf(discriminant)) / (2 * params.x);
//     if (res[0] > EPSILON)
//         check_height(ray, &(obj->cone), &(res[0]));
//     if (res[1] > EPSILON)
//         check_height(ray, &(obj->cone), &(res[1]));
//     dist_cap = dist_caps(ray, obj);
//     res[0] = which_pos_min(res[0], res[1], dist_cap);
//     if (res[0] == dist_cap && res[0] != FLT_MAX)
//         obj->cone.disk_hit = 1;
//     return res[0];
// }





// float cone_intersection(float delta, float a, float b)
// {
//     float intersect_1 = (-b - sqrt(delta)) / (2 * a);
//     float intersect_2 = (-b + sqrt(delta)) / (2 * a);
//     if (intersect_2 > EPSILON && intersect_1 > intersect_2)
//         return intersect_2;
//     else if (intersect_1 > EPSILON)
//         return intersect_1;
//     return FLT_MAX;
// }

// static float get_intersect(const t_ray *ray, t_object *obj)
// {
//     t_vec3 oc = vec3_sub(ray->origin, obj->cone.vertex);
//     float cos_squared = cosf(obj->cone.angle) * cosf(obj->cone.angle);
//     float a = vec3_dot(ray->direction, ray->direction) - (1.0f + cos_squared) *
//         vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(ray->direction, obj->cone.normal);
//     float b = 2.0f * (vec3_dot(ray->direction, oc) - (1.0f + cos_squared) *
//         vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
//     float c = vec3_dot(oc, oc) - (1.0f + cos_squared) * vec3_dot(oc, obj->cone.normal) *
//         vec3_dot(oc, obj->cone.normal);
//     float discriminant = b * b - 4.0f * a * c;
//     float intersection = FLT_MAX;

//     if (discriminant > EPSILON)
//     {
//         float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
//         float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);
//         float z1 = t1 * obj->cone.normal.z + vec3_dot(ray->direction, obj->cone.normal);
//         float z2 = t2 * obj->cone.normal.z + vec3_dot(ray->direction, obj->cone.normal);

//         if (t1 > EPSILON && z1 > 0 && z1 <= obj->cone.height)
//             intersection = t1;
//         else if (t2 > EPSILON && z2 > 0 && z2 <= obj->cone.height)
//             intersection = t2;
//     }

//     return intersection;
// }

// float dist_cone(const t_ray *ray, t_object *obj)
// {
//     t_vec3 direction = vec3_multf(obj->cone.normal, obj->cone.height);
//     obj->cone.vertex = vec3_sub(obj->cone.pos, direction);
//     float t = get_intersect(ray, obj);
//     if (t == FLT_MAX)
//         return FLT_MAX;
//     t_vec3 intersection_point = vec3_add(ray->origin, vec3_multf(ray->direction, t));
//     if (t > EPSILON)
//     {
//         t_vec3 diff = vec3_sub(intersection_point, obj->cone.vertex);
//         float check = vec3_dot(diff, obj->cone.normal);
//         if (check < EPSILON)
//             return FLT_MAX;
//         float height_squared = vec3_dot(diff, diff);
//         float max_height_squared = obj->cone.height * obj->cone.height;
//         if (height_squared < max_height_squared)
//             return t;
//     }
//     return FLT_MAX;
// }



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
    t_vec3 oc = vec3_sub(ray->origin, obj->cone.vertex);
    float cos_squared = cosf(obj->cone.angle) * cosf(obj->cone.angle);
    float a = vec3_dot(ray->direction, ray->direction) - (1.0f + cos_squared) *
              vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(ray->direction, obj->cone.normal);
    float b = 2.0f * (vec3_dot(ray->direction, oc) - (1.0f + cos_squared) *
                      vec3_dot(ray->direction, obj->cone.normal) * vec3_dot(oc, obj->cone.normal));
    float c = vec3_dot(oc, oc) - (1.0f + cos_squared) * vec3_dot(oc, obj->cone.normal) *
              vec3_dot(oc, obj->cone.normal);
    float discriminant = b * b - 4.0f * a * c;
    float intersection = FLT_MAX;

    if (discriminant > EPSILON)
    {
        float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);
        float y1 = ray->origin.y + t1 * ray->direction.y;
        float y2 = ray->origin.y + t2 * ray->direction.y;

        if (y1 > obj->cone.vertex.y && y1 < (obj->cone.vertex.y + obj->cone.height))
            intersection = t1;
        else if (y2 > obj->cone.vertex.y && y2 < (obj->cone.vertex.y + obj->cone.height))
            intersection = t2;
    }

    return intersection;
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


