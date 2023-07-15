/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:09:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 16:06:03 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"

t_vec2	capped_cylinder_map(t_vec3 point, t_object *obj)
{
	t_vec2	uv;
	t_vec3	offset;
	t_vec3	projection;
	float	angle;

	offset = vec3_sub(point, obj->cylinder.pos);
	projection = vec3_sub(offset, vec3_multf(obj->cylinder.normal,
				dot_product(offset, obj->cylinder.normal)));
	angle = atan2(projection.z, projection.x);
	if (angle < 0.0)
		angle += 2.0f * M_PI;
	uv.x = angle * M_1_DIV_2PI;
	uv.y = (offset.y - obj->cylinder.pos.y) / obj->cylinder.height;
	return (uv);
}
