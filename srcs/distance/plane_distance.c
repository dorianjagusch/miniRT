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


double    dist_plane(t_ray *ray, t_obj *obj)
{
    double    p_dist;
    double    angle;
    double    temp;

    // printf("------------\n");
    // printf("Origin: x: %f y: %f z: %f\n", ray->origin.x, ray->origin.y, ray->origin.z);
    // printf("Position: x: %f y: %f z: %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
    // printf("Normal: x: %f y: %f z: %f\n", obj->normal.x, obj->normal.y, obj->normal.z);
   // print_vec3(obj->normal, "before norm");
    vec3_normalize(&obj->normal);
    //print_vec3(obj->norma674540l, "after norm");
    //angle = vec3_dot(vec3_multf(ray->direction, -1), obj->normal);
    angle = vec3_dot(obj->normal, ray->direction);
   printf("angle: %f\n", angle);
    if (angle < 0.00000001)
        return (DBL_MAX);
    temp = vec3_dot(vec3_sub(ray->origin, obj->position), vec3_multf( obj->normal, -1));
    p_dist = temp / sqrt(angle);
    printf("p_dist = %f\n", p_dist);
    if (p_dist > 0)
        return (p_dist);
    
    return (DBL_MAX);
}


// double	dist_plane(t_ray *ray, t_obj *obj)
// {
// 	double	p_dist; // what does this do
// 	double	angle;
// 	double	temp;
	
// 	printf("------------\n");
// 	printf("Origin: x: %f y: %f z: %f\n", ray->origin.x, ray->origin.y, ray->origin.z);
// 	printf("Position: x: %f y: %f z: %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
// 	printf("Normal: x: %f y: %f z: %f\n", obj->normal.x, obj->normal.y, obj->normal.z);
// 	//vec3_normalize(&obj->normal); // does this work
// 	angle = vec3_dot(obj->normal, ray->direction);
// 	printf("angle: %f\n", angle);
// 	if (angle < 0.001)
// 		return (DBL_MAX);
// 	temp = vec3_sub(ray->origin, obj->position); //do we need it
// 	p_dist /= angle;
// 	printf("p_dist = \n", p_dist);
// 	if (p_dist > 0)
// 		return (p_dist);
// 	return (DBL_MAX);
// }

