/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_math.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:07:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 12:13:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_MATH_H
# define MAT4_MATH_H

typedef struct s_mat4 {
	float	data[4][4];
}			t_mat4;


t_mat4	mat4_mult(t_mat4 lmatrix, t_mat4 rmatrix);
t_mat4	mat4_add(t_mat4 matrix1, t_mat4 matrix2);
t_mat4	mat4_sub(t_mat4 matrix1, t_mat4 matrix2);
t_mat4	mat4_det(t_mat4 matrix);

#endif