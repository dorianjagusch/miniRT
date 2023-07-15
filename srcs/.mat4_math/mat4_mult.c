/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:17:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 13:51:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4_math.h"

t_mat4	mat4_mult(t_mat4 lmat, t_mat4 rmat)
{
	t_mat4	result;
	int		row;
	int		col;
	int		k;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
		{
			result.data[row][col] = 0.0;
			k = -1;
			while (++k < 4)
				result.data[row][col] += lmat.data[row][k] * rmat.data[k][col];
		}
	}
	return (result);
}

t_mat4	mat4_multf(t_mat4 mat, double val)
{
	t_mat4	result;
	int		row;
	int		col;
	int		k;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
			result.data[row][col] = mat.data[row][col] * val;
	}
	return (result);
}

t_vec3	mat4_mult_vec3(const t_mat4 matrix, const t_vec3 vec)
{
	t_vec3	result;

	result.x = matrix.data[0][0] * vec.x + matrix.data[1][0] * vec.y + \
		matrix.data[2][0] * vec.z + matrix.data[3][0];
	result.y = matrix.data[0][1] * vec.x + matrix.data[1][1] * vec.y + \
		matrix.data[2][1] * vec.z + matrix.data[3][1];
	result.z = matrix.data[0][2] * vec.x + matrix.data[1][2] * vec.y + \
		matrix.data[2][2] * vec.z + matrix.data[3][2];

	return (result);
}
