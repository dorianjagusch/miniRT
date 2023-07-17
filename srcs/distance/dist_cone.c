/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:46:14 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/17 22:49:41 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// int quadratic(double a, double b, double c, double x[2]) {
//   if (a == 0.0) return 0;
//   double d = b*b - 4*a*c;
//   if (d < 0.0) return -1;
//   d = sqrt(d);
//   x[0] = (-b + d) / (2 * a);
//   x[1] = (-b - d) / (2 * a);
//   return 2;
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
		return (intersect_2);
	else
		return (intersect_1);
}

static void	calc_temps_cone(const t_ray *ray, const t_cone *cone,
		t_vec3 *temp)
{
	temp[ORTHO] = vec3_sub(ray->direction, vec3_multf(cone->normal,
				vec3_dot(ray->direction, cone->normal)));
	temp[AXIS] = vec3_sub(vec3_sub(ray->origin, cone->pos),
			vec3_multf(cone->normal,
				vec3_dot(vec3_sub(ray->origin, cone->pos),
					cone->normal)));
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
	t_vec3	temp[2];

	t_vec3 translated_origin = vec3_sub(ray->origin, cone->cone.pos);
	posdiff_x = translated_origin.x - cone->cone.center.x;
	posdiff_z = translated_origin.z - cone->cone.center.z;
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