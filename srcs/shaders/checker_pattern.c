/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:58:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/19 16:31:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "patterns.h"

t_checkers	set_board(int width, int height, t_vec4 light, t_vec4 dark)
{
	t_checkers	board;

	board.width = width;
	board.height = height;
	board.light = light;
	board.dark = dark;
	return (board);
}

t_vec4	get_checkers(t_texture *texture, t_vec2 uv)
{
	int	int_u;
	int	int_v;

	int_u = (int)floor(uv.y * texture->checkers.height);
	int_v = (int)floor(uv.x * texture->checkers.width);
	if ((int_u + int_v) & 0x01)
		return (texture->checkers.light);
	else
		return (texture->checkers.dark);
}