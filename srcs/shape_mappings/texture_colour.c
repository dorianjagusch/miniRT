/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:55:38 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/17 16:43:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "minirt.h"
#include "patterns.h"

t_vec4	get_texture_colour(t_object *object, t_vec3 *point)
{
	static const t_col_func	colour_func[] = {
		get_checkers
	};
	static const t_map_func	map_func[] = {
		spherical_map,
		plane_map,
		cylinder_map,
		plane_map,
		plane_map
	};
	t_vec4					colour;
	t_vec2					uv;
	t_texture				*texture;

	uv = map_func[object->type](point, object);
	texture = object->sphere.texture;
	colour = colour_func[0](texture, uv);
	return (colour);
}
