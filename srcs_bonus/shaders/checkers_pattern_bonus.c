/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_pattern_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:58:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 14:28:41 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include "patterns_bonus.h"

t_proc_pat	set_board(int width, int height, t_vec4 light, t_vec4 dark)
{
	t_proc_pat	board;
	
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

	int_u = (int)floor(uv.y * texture->proc_pat.height);
	int_v = (int)floor(uv.x * texture->proc_pat.width);
	if ((int_u + int_v) & 0x01)
		return (texture->proc_pat.light);
	else
		return (texture->proc_pat.dark);
}
