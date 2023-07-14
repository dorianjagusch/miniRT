/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:58:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/14 09:01:43 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "patterns.h"

t_checker_board	set_board(int width, int height, t_vec4 light, t_vec4 dark)
{
	t_checker_board	board;

	board.width = width;
	board.height = height;
	board.light = light;
	board.dark = dark;
	return (board);
}

t_vec4	get_checker(t_checker_board *checkers, t_vec2 uv)
{
	int	int_u;
	int	int_v;

	int_u = (int)floor(uv.x * checkers->width);
	int_v = (int)floor(uv.y * checkers->height);

	if ((int_u + int_v) % 2 == 0)
		return (checkers->light);
	else
		return (checkers->dark);
}
