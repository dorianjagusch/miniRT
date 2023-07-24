/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:55:38 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 19:08:49 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "minirt.h"
#include "patterns.h"

t_vec4	get_texture_col(t_texture *texture, t_vec2 uv)
{
	int		*dst;
	t_vec4	colour;
	t_vec2	pxl;
	static int	i;
	int			check;

	pxl.x = uv.x * (texture->picture.width - 1) ;
	pxl.y = uv.y * (texture->picture.height - 1);
	g_i++;
	dst = (int *)(texture->picture.addr
			+ (int)pxl.y * texture->picture.line_length
			+ (int)pxl.x * (texture->picture.bits_per_pixel / 8));
	colour = ft_int32tov4(*dst);
	check = i++;
	ft_rgbtonorm(&colour);
	return (colour);
}

t_vec4	get_texture_colour(t_object *object, t_vec3 *point)
{
	DEBUG_ONLY(printf("in get_texture\n"));
	static const t_col_func	colour_func[] = {
		get_checkers,
		get_brick,
		get_texture_col
	};

	static const t_map_func	map_func[] = {
		spherical_map,
		plane_map,
		cylinder_map,
		disk_map,
		triangle_map,
		cone_map
	};
	t_vec4					colour;
	t_vec2					uv;
	t_texture				*texture;

	DEBUG_ONLY(printf("object id: %d\n", object->type));
	uv = map_func[object->type](point, object);
	texture = object->meta.tex_col;
	colour = colour_func[texture->pattern](texture, uv);
	return (colour);
}
