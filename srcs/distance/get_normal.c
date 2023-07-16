/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/16 16:06:06 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "minirt.h" //


t_vec3	get_cylinder_normal( t_cylinder *cylinder, const t_vec3 hitpoint)
{
	t_vec3	co;
	t_vec3	normal;

	if (cylinder->disk_hit)
	{
		normal = cylinder->normal;
		cylinder->disk_hit = 0;
	}
	else
	{
		co = vec3_sub(hitpoint, cylinder->pos);
		normal = vec3_sub(co, vec3_multf(cylinder->normal,
					vec3_dot(cylinder->normal, co)));
	}
	return (normal);
}

// t_vec3 get_cone_normal(t_object *cone, t_vec3 hitpoint)
// {
// 	// Calculate the radial distance from the cone's center
// 	float rad_dist = sqrt((hitpoint.x - cone->cone.center.x) * (hitpoint.x - cone->cone.center.x) + (hitpoint.z - cone->cone.center.z) * (hitpoint.z - cone->cone.center.z));
// 	// Calculate the normal t_vec3 with adjusted y-component
// 	t_vec3 normal = {hitpoint.x - cone->cone.center.x, rad_dist * (cone->cone.radius / cone->cone.height), hitpoint.z - cone->cone.center.z};
// 	// Normalize the normal t_vec3
	
// 	return (normal); // Return the normalized normal t_vec3
// }
t_vec3	get_cone_normal(t_cone *cone, t_vec3 hitpoint)
{
	t_vec3	co;
	t_vec3	normal;

	if (cone->disk_hit)
	{
		normal = cone->normal;
		cone->disk_hit = 0;
	}
	else
	{
		co = vec3_sub(hitpoint, cone->pos);
		normal = vec3_sub(co, vec3_multf(cone->normal,
					vec3_dot(cone->normal, co)));
	}
	return (normal);
}


t_vec3	get_normal(t_object *obj, t_vec3 hitpoint)
{
	t_vec3	normal;

	if (obj->type == sphere_obj)
		normal = vec3_sub(hitpoint, obj->sphere.pos);
	else if (obj->type == mesh_obj)
		normal = obj->mesh.triangle_data[obj->mesh.obj_id].triangle.normal;
	else if (obj->type == plane_obj)
		return (obj->plane.normal);
	else if (obj->type == disk_obj)
		return (obj->disk.normal);
	else if (obj->type == triangle_obj)
		normal = vec3_cross(obj->triangle.edges[1], obj->triangle.edges[0]);
	else if (obj->type == cylinder_obj)
		normal = get_cylinder_normal(&(obj->cylinder), hitpoint);
	else if (obj->type == cone_obj)
		normal = get_cone_normal(&(obj->cone), hitpoint);
	else if (obj->type == box_obj)
		return (obj->box.normal);
	vec3_normalize(&normal);
	return (normal);
}
