/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:06:37 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 21:46:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3	vec3_rotate(t_vec3 vec, t_vec3 normal)
{
	t_vec3	rot_vec;

	rot_vec.x = vec3_dot(vec, normal);
	rot_vec.y = vec.y * normal.x - vec.x * normal.y;
	rot_vec.z = vec.z * normal.x - vec.x * normal.z;
	return (rot_vec);
}