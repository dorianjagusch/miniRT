/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 16:22:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

static t_vec3	get_cylinder_normal(t_cylinder *cylinder, const t_vec3 hitpoint)
{
	t_vec3	co;
	t_vec3	normal;

	if (cylinder->disk_hit)
	{
		normal = cylinder->bottom->disk.normal;
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

t_vec3	get_normal(t_object *obj, t_vec3 hitpoint)
{
	t_vec3	normal;

	if (obj->type == sphere_obj)
		normal = vec3_sub(hitpoint, obj->sphere.pos);
	else if (obj->type == plane_obj)
		return (obj->plane.normal);
	else if (obj->type == disk_obj)
		return (obj->disk.normal);
	else if (obj->type == cylinder_obj)
		normal = get_cylinder_normal(&(obj->cylinder), hitpoint);
	else if (obj->type == cone_obj)
		normal = get_cone_normal(&(obj->cone), hitpoint);
	vec3_normalize(&normal);
	return (normal);
}