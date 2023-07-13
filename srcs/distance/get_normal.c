/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/13 11:31:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"
#include "minirt.h" //

t_vec3	get_normal(t_object *obj, t_vec3 hitpoint)
{
	t_vec3	normal;
	t_vec3	co;
	DEBUG_ONLY(printf("IN GET NORMAL\n"));
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
	{
		DEBUG_ONLY(printf("cylinder\n"));
		co = vec3_sub(hitpoint, obj->cylinder.pos);
		normal = vec3_sub(co, vec3_multf(obj->cylinder.normal,
					vec3_dot(obj->cylinder.normal, co)));
	}
	else if (obj->type == box_obj)
		return (obj->box.normal);
	DEBUG_ONLY(printf("Normalize\n"));
	vec3_normalize(&normal);
	DEBUG_ONLY(printf("exit get normal\n"));
	return (normal);
}
