/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_inv_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:17:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:32:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include <float.h>

#ifndef EPSILON
# define EPSILON 10e-3
#endif

t_vec3	vec3_inv(const t_vec3 v)
{
	t_vec3	res;

	res = (t_vec3){FLT_MAX, FLT_MAX, FLT_MAX};
	if (v.x > EPSILON)
		res.x = 1.0 / v.x;
	if (v.y > EPSILON)
		res.y = 1.0 / v.y;
	if (v.z > EPSILON)
		res.z = 1.0 / v.z;
	return (res);
}
