/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/26 18:59:03 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"

t_vec3	get_normal(t_obj *obj, t_vec3 hitpoint)
{
	t_vec3	normal;

	if (obj->type == sphere)
	{
		normal = vec3_sub(hitpoint, obj->position);
		vec3_normalize(&normal);
		return (normal);
	}
	else if (obj->type == plane)
		return (obj->normal);
	else if (obj->type == cylinder)
		return ((t_vec3){0});
	return ((t_vec3){0});
}
