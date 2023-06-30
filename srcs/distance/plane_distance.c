/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/28 16:08:25 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"

// double dist_plane(t_ray *ray, t_obj *obj)
// {
//     double  denominator;
//     double  signed_dist;
//     double  p_dist;

//     denominator = vec3_dot(ray->direction, obj->normal);
//     signed_dist = vec3_dot(obj->normal, ray->origin) + obj->d;

//     if (denominator > EPSILON && signed_dist > EPSILON)
//         return DBL_MAX;
//     if (denominator < EPSILON && signed_dist <= EPSILON)
//         return DBL_MAX;

//     p_dist = (-obj->d - vec3_dot(ray->origin, obj->normal)) / denominator;

//     // Check if the intersection point is within the disk
//     t_vec3 intersection_point = vec3_add(ray->origin, vec3_multf(ray->direction, p_dist));
//     t_vec3 disk_center = obj->position;

//     double disk_radius = 5.0;
//     // double distance_to_center = vec3_dist(intersection_point, disk_center);

//     if (p_dist >= 0.0 && distance_to_center <= disk_radius)
//         return p_dist;
// }

double    dist_plane(t_ray *ray, t_obj *obj)
{
	double denominator;
    double signed_dist;
    double p_dist;

	denominator = vec3_dot(ray->direction, obj->normal);
    signed_dist = vec3_dot(obj->normal, ray->origin) + obj->d;
    if (denominator > EPSILON && signed_dist > EPSILON)
        return (DBL_MAX);
    if (denominator <  EPSILON && signed_dist <= EPSILON)
        return (DBL_MAX);
    p_dist = (-obj->d - vec3_dot(ray->origin, obj->normal)) / denominator;
    if (p_dist >= 0.0)
        return (p_dist);
    return (DBL_MAX);
}
