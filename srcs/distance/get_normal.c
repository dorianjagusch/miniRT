/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 21:27:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "vector_math.h"


t_vec3	get_normal(t_obj *obj, t_vec3 hitpoint)
{
	if (obj->type == sphere)
		return (ft_v3norm(ft_v3sub(hitpoint, obj->radius)));
	else if (obj->type == plane)
		return (obj->normal);
	else if (obj->type == cylinder)
		return ((t_vec3){0});
}