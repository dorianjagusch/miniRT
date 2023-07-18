/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:46:14 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/18 10:17:36 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	posdiff_x = translated_origin.x - cone->cone.center.x;
	posdiff_z = translated_origin.z - cone->cone.center.z;
	height_diff = cone->cone.height - ray->origin.y;
	qudratics[0] = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z) - (cone->cone.angle * (ray->direction.y * ray->direction.y));
	qudratics[1] = (2 * posdiff_x * ray->direction.x) + (2 * posdiff_z * ray->direction.z) + (2 * cone->cone.angle * height_diff * ray->direction.y);
	qudratics[2] = (posdiff_x * posdiff_x) + (posdiff_z * posdiff_z) - (cone->cone.angle * (height_diff * height_diff));
	delta = qudratics[1] * qudratics[1] - 4 * (qudratics[0] * qudratics[2]);
	cone->cone.disk_hit = dist_disk(ray, cone->cone.bottom);
	intersect = cone_intersection(delta, qudratics[0], qudratics[1]);
	intersect_y = ray->origin.y + intersect * ray->direction.y;
	if (intersect >= cone->cone.disk_hit && intersect_y >= 0 && intersect_y <= cone->cone.height)
	{
		intersect = cone->cone.height - intersect_y;
		return (intersect);
	}
	else if (cone->cone.disk_hit > EPSILON)
	{	
		cone->cone.disk_hit = 1;
		intersect = cone->cone.height - (cone->cone.height - intersect_y);
		return (intersect);
	}
	return (FLT_MAX);
}