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

#include "shaders.h"
#include <stdio.h>//

/*bool intersectPlane(const Vec3f &n, const Vec3f &p0, const Vec3f &l0, const Vec3f &l, float &t)
{
    // assuming vectors are all normalized
    float denom = dotProduct(n, l);
    if (denom > 1e-6) {
        Vec3f p0l0 = p0 - l0;
        t = dotProduct(p0l0, n) / denom; 
        return (t >= 0);
    }
    return false;
}*/

double    dist_plane(t_ray *ray, t_obj *obj)
{
    double  p_dist; //t
	double  denominator;

	denominator = vec3_dot(ray->direction, obj->normal);
    //denominator = vec3_dot(ray->direction, vec3_multf(obj->normal, -1)); //do we need to invert
	if (denominator == 0)
		return (DBL_MAX);
	p_dist = (vec3_dot(vec3_multf(obj->normal, -1), vec3_sub(obj->position, ray->origin))) / denominator;
	
	if (denominator > 1e-6)//
        return p_dist;
   else
        return DBL_MAX;
}
