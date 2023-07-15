/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:30:23 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 12:31:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4_math.h"

t_mat4	mat4_add(t_mat4 mat1, t_mat4 mat2)
{
	t_mat4	result;
	int		row;
	int		col;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
			result.data[row][col] = mat1.data[row][col] + mat2.data[row][col];
	}
	return (result);
}
