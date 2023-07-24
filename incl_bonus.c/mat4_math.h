/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_math.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:07:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 13:51:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_MATH_H
# define MAT4_MATH_H

# include "vector_math.h"

typedef struct s_mat4
{
	float	data[4][4];
}			t_mat4;

t_mat4	mat4_mult(t_mat4 lmatrix, t_mat4 rmatrix);
t_mat4	mat4_add(t_mat4 matrix1, t_mat4 matrix2);
t_mat4	mat4_sub(t_mat4 matrix1, t_mat4 matrix2);
t_mat4	mat4_rotate_x(float angle);
t_mat4	mat4_rotate_y(float angle);
t_mat4	mat4_identity(void);
t_vec3	mat4_mult_vec3(const t_mat4 matrix, const t_vec3 vec);

#endif