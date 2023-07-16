/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:46:14 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/16 15:53:07 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float cone_intersection(float delta, float a, float b)
{
	float intersect_1;
	float intersect_2;

	intersect_1 = (-b - sqrt(delta)) / (2 * a);
	intersect_2 = (-b + sqrt(delta)) / (2 * a);
	if (intersect_1 > intersect_2)
		return (intersect_2);
	else
		return (intersect_1);

}




float	dist_cone(const t_ray *ray, t_object *cone)
{
	float posdiff_x;
	float posdiff_z;
	float height_diff;
	float tan_sq;
	float qudratics[3]; //a = 0, b = 1, c = 2
	float intersect;
	float intersect_y;
	float delta;

	posdiff_x = ray->origin.x - cone->cone.center.x;
	posdiff_z = ray->origin.z - cone->cone.center.z;
	height_diff = cone->cone.height - ray->origin.y + cone->cone.center.y;
	tan_sq = (cone->cone.radius / cone->cone.height) * (cone->cone.radius / cone->cone.height);
	qudratics[0] = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z) - (tan_sq * (ray->direction.y * ray->direction.y));
	qudratics[1] = (2 * posdiff_x * ray->direction.x) + (2 * posdiff_z* ray->direction.z) + (2 * tan_sq * height_diff * ray->direction.y);
	qudratics[2]= (posdiff_x * posdiff_x) + (posdiff_z* posdiff_z) - (tan_sq * (height_diff * height_diff));
	delta = qudratics[1] * qudratics[1] - 4 * (qudratics[0] * qudratics[2]);
    cone->cone.disk_hit = dist_disk(ray, cone->cone.bottom);
    intersect = cone_intersection(delta, qudratics[0], qudratics[1]);
    intersect_y = ray->origin.y + intersect * ray->direction.y;
	if (intersect > cone->cone.disk_hit && intersect_y > cone->cone.center.y && intersect_y < cone->cone.center.y + cone->cone.height) 
    	return (intersect);
	else if (cone->cone.disk_hit > EPSILON)
		return (cone->cone.disk_hit);
    return (FLT_MAX);
}



