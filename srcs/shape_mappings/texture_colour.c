/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:55:38 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/13 19:46:12 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "minirt.h"
#include "patterns.h"

t_vec4	get_texture_colour(t_vec4 (*pattern)(t_checker_board *, t_vec2),
	t_vec2 (*map)(t_object *, t_vec3 *), t_object *object, t_vec3 *point,
	t_checker_board *checkers)
{
	t_vec4	colour;

	colour = pattern(checkers, map(object, point));
	return (colour);
}
