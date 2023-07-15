/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:56:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 13:21:49 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4_math.h"

t_mat4	mat4_rotate_x(float angle)
{
	t_mat4	result;
	float	cos_theta;
	float	sin_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	result = mat4_identity();
	result.data[1][1] = cos_theta;
	result.data[1][2] = -sin_theta;
	result.data[2][1] = sin_theta;
	result.data[2][2] = cos_theta;
	return (result);
}

t_mat4	mat4_rotate_y(float angle)
{
	t_mat4	result;
	float	cos_theta;
	float	sin_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	result = mat4_identity();
	result.data[0][0] = cos_theta;
	result.data[0][2] = sin_theta;
	result.data[2][0] = -sin_theta;
	result.data[2][2] = cos_theta;
	return (result);
}
