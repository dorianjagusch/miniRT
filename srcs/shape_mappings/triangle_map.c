/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:09:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/19 08:24:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"
#include "objects.h"
#include <unistd.h>

// t_vec2	triangle_map(t_vec3 *point, t_object *obj)
// {
// 	t_vec3	upright;
// 	t_vec3	edge1;
// 	t_vec3	edge2;
// 	float	angle;
// 	t_vec2	uv;

// 	uv = obj->triangle.uv;
// 	// if (ft_strcmp(obj->triangle.texture->file, "checkers"))
// 	// {
// 		edge1 = obj->triangle.edges[0];
// 		edge2 = obj->triangle.edges[1];
// 		vec3_normalize(&edge1);
// 		vec3_normalize(&edge2);
// 		upright = vec3_cross(obj->triangle.normal, edge1);
// 	// }
// 	// printf("U: %f\tV: %f\tmod2: %d\n", uv.x, uv.y, (int)(uv.x + uv.y));
// 	return (uv);	
// }

t_vec2	triangle_map(t_vec3 *point, t_object *obj)
{
	float	w;
	t_vec2	uv;

	w = 1.0f - obj->triangle.uv.x - obj->triangle.uv.y;
	uv = vec2_add(vec2_add(vec2_multf((t_vec2){0, 0}, obj->triangle.uv.x),
				vec2_multf((t_vec2){0, 1}, obj->triangle.uv.x)),
			vec2_multf((t_vec2){1, 0}, w));
	return (uv);
}
