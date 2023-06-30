/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:11:40 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 18:03:03 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "minirt.h"
#include <float.h>

// double	dist_cylinder(t_ray *ray, t_obj *obj)
// {
// 	t_ray	rot_ray;
// 	t_vec3	params;
// 	t_vec2	res;
// 	double	discriminant;

// 	// rot_ray->origin = vec3_rotate(ray->origin, obj->normal);
// 	// rot_ray.direction = vec3_rotate(ray->direction, obj->normal);
// 	params.x = ray->direction.x * ray->direction.x + \
// 			ray->direction.z * ray->direction.z;
// 	params.y = 2.0 * (ray->origin.x * ray->direction.x + \
// 			ray->origin.z * ray->direction.z);
// 	params.z = ray->origin.x * ray->origin.x + \
// 			ray->origin.z * ray->origin.z - obj->radius2;
// 	discriminant = params.y * params.y - 4.0 * params.x * params.z;
// 	if (discriminant < 0.0)
// 		return (DBL_MAX);
// 	res.x = (-params.y + sqrt(discriminant)) / (2.0 * params.x);
// 	res.y = (-params.y - sqrt(discriminant)) / (2.0 * params.x);
// 	if (res.x > 0.0 && fabs(ray->origin.y + res.x * ray->direction.y) \
// 			<= obj->height)
// 		return (res.x);
// 	if (res.y > 0.0 && fabs(ray->origin.y + res.y * ray->direction.y) \
// 			<= obj->height)
// 		return (res.y);
// 	return (DBL_MAX);
// }


double dist_cylinder(t_ray *ray, t_obj *cylinder)
{
	t_vec3	pot_hit;
	t_vec3	temp;
	double	point_dist;
	double	t;
	t_vec3	caps[2];

	printf("here\n");
	t = vec3_dot(ray->direction, vec3_sub(cylinder->pos, ray->origin));
	DEBUG_ONLY(printf("cosangle: %d\n"));
	pot_hit = vec3_add(ray->origin, vec3_multf(ray->direction, t));
	DEBUG_ONLY(print_vec3(pot_hit, "potential hit"));
	temp = vec3_sub(pot_hit, cylinder->pos);
	point_dist = sqrt(vec3_mag(temp));
	if (pot_hit.y <= cylinder->pos.y + cylinder->height
		&& pot_hit.y >= cylinder->pos.y - cylinder->height
		&& point_dist <= cylinder->radius)
		return (vec3_mag(vec3_sub(ray->origin, pot_hit)));
	else
	{
		caps[0] = cylinder->pos;
		caps[0].y -= cylinder->height;
		caps[1] = cylinder->pos;
		caps[1].y += cylinder->height;
		return (vec3_dist(ray->origin, caps[0]),
			vec3_dist(ray->origin, caps[1]));
	}
}
