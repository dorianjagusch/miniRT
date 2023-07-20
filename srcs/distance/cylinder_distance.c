/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:11:40 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/20 07:24:27 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "minirt.h"
#include <float.h>

float	which_pos_min(float a, float b, float c)
{
	float	min;

	min = a;
	if (b > EPSILON && b < min)
		min = b;
	if (c > EPSILON && c < min)
		min = c;
	if (min > EPSILON)
		return (min);
	return (FLT_MAX);
}

float	dist_caps(const t_ray *ray, const t_object *obj)
{
	float	dist;

	dist = dist_disk(ray, obj->cylinder.bottom);
	dist = fminf(dist_disk(ray, obj->cylinder.top), dist);
	return (dist);
}

static void	check_height(const t_ray *ray, const t_cylinder *cylinder,
			float *dist)
{
	t_vec3	hitpoint;
	t_vec3	top_cap;
	t_vec3	bottom_cap;
	float	cap_dist;

	top_cap = vec3_add(cylinder->pos, vec3_multf(cylinder->normal,
				cylinder->height / 2));
	bottom_cap = vec3_sub(cylinder->pos, vec3_multf(cylinder->normal,
				cylinder->height / 2));
	hitpoint = vec3_add(ray->origin, vec3_multf(ray->direction, *dist));
	if (vec3_dot(cylinder->normal, vec3_sub(hitpoint, bottom_cap)) <= EPSILON)
		*dist = FLT_MAX;
	if (vec3_dot(cylinder->normal, vec3_sub(hitpoint, top_cap)) >= EPSILON)
		*dist = FLT_MAX;
}

static void	calc_temps(const t_ray *ray, const t_cylinder *cylinder,
		t_vec3 *temp)
{
	temp[ORTHO] = vec3_sub(ray->direction, vec3_multf(cylinder->normal,
				vec3_dot(ray->direction, cylinder->normal)));
	temp[AXIS] = vec3_sub(vec3_sub(ray->origin, cylinder->pos),
			vec3_multf(cylinder->normal,
				vec3_dot(vec3_sub(ray->origin, cylinder->pos),
					cylinder->normal)));
}

float	dist_cylinder(const t_ray *ray, t_object *obj)
{
	t_vec3	temp[2];
	t_vec3	params;
	float	discriminant;
	float	res[2];
	float	dist_cap;

	calc_temps(ray, &(obj->cylinder), temp);
	params.x = vec3_dot(temp[0], temp[0]);
	params.y = 2 * vec3_dot(temp[0], temp[1]);
	params.z = vec3_dot(temp[1], temp[1]) - (obj->cylinder.radius2);
	discriminant = params.y * params.y - 4 * params.x * params.z;
	if (discriminant < EPSILON)
		return (FLT_MAX);
	res[0] = (-params.y - sqrt(discriminant)) / (2 * params.x);
	res[1] = (-params.y + sqrt(discriminant)) / (2 * params.x);
	if (res[0] > EPSILON)
		check_height(ray, &(obj->cylinder), &(res[0]));
	if (res[1] > EPSILON)
		check_height(ray, &(obj->cylinder), &(res[1]));
	dist_cap = dist_caps(ray, obj);
	res[0] = which_pos_min(res[0], res[1], dist_cap);
	if (res[0] == dist_cap && res[0] != FLT_MAX)
		obj->cylinder.disk_hit = 1;
	return (res[0]);
}
