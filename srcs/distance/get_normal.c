/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/04 15:54:46 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"

t_vec3	get_normal(t_obj *obj, t_vec3 hitpoint)
{
	t_vec3	normal;
	t_vec3	co;

	if (obj->type == sphere)
		normal = vec3_sub(hitpoint, obj->pos);
	else if (obj->type == plane || obj->type == disk)
		return (obj->normal);
	else if (obj->type == cylinder)
	{
		co = vec3_sub(hitpoint, obj->pos);
		normal = vec3_sub(co, vec3_multf(obj->normal,
					vec3_dot(obj->normal, co)));
	}
	vec3_normalize(&normal);
	return (normal);
}
