/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:11:40 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/06 00:44:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "minirt.h"
#include <float.h>

// The cylinder is a little tricky. For now I leave this annotated because I am
// not sure, I'll understand this on Monday still.

void	dist_cap(const t_ray *ray, const t_object *obj, double dist_caps[2])
{
	t_disk	top_cap;

	top_cap.pos = vec3_add(obj->cylinder.pos, vec3_multf(obj->cylinder.normal,
				obj->cylinder.height));
	top_cap.normal = obj->cylinder.normal;
	top_cap.radius = obj->cylinder.radius;
	// dist_caps[0] = dist_disk(ray, obj);
	// dist_caps[1] = dist_disk(ray, &top_cap);
}

/* The distance to the caps of the hitpoint is calculated here. Both are checked
against the hitpoint positions.
*/
static void	check_height(const t_ray *ray, const t_cylinder *cylinder,
			double *dist)
{
	t_vec3	hitpoint;
	t_vec3	top_cap;
	double	cap_dist;

	top_cap = vec3_add(cylinder->pos, vec3_multf(cylinder->normal,
				cylinder->height));
	hitpoint = vec3_add(ray->origin, vec3_multf(ray->direction, *dist));
	if (vec3_dot(cylinder->normal, vec3_sub(hitpoint, cylinder->pos)) <= 0)
	{
		*dist = DBL_MAX;
	}
	if (vec3_dot(cylinder->normal, vec3_sub(hitpoint, top_cap)) >= 0)
	{
		*dist = DBL_MAX;
	}
}

/* ORTHO calculates the component of the ray direction vector that is orthogonal to the base position
 (for now that is the position that the cylinder rest on if it was standing)
Axis is similarly the component of the ray origin along the axis.*/

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

double	dist_cylinder(const t_ray *ray, const t_object *obj)
{
	t_vec3	temp[2];
	t_vec3	params;
	double	discriminant;
	double	res[2];
	double	dist_caps[2];

	calc_temps(ray, &(obj->cylinder), temp);
	params.x = vec3_dot(temp[0], temp[0]);
	params.y = 2 * vec3_dot(temp[0], temp[1]);
	params.z = vec3_dot(temp[1], temp[1]) - (obj->cylinder.radius2);
	discriminant = params.y * params.y - 4 * params.x * params.z;
	if (discriminant < EPSILON)
		return (DBL_MAX);
	res[0] = (-params.y - sqrt(discriminant)) / (2 * params.x);
	res[1] = (-params.y + sqrt(discriminant)) / (2 * params.x);
	if (res[0] > EPSILON)
		check_height(ray, &(obj->cylinder), &(res[0]));
	if (res[1] > EPSILON)
		check_height(ray, &(obj->cylinder), &(res[1]));
	dist_cap(ray, obj, dist_caps);
	if (res[0] < res[1] && res[0] > EPSILON)
		return (res[0]);
	else if (res[1] != DBL_MAX && res[1] > EPSILON)
		return (res[1]);
	return (DBL_MAX);
}
