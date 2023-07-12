/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_inv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:17:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/12 13:54:00 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

#ifndef EPSILON
# define EPSILON 1e-3
#endif

t_vec3	vec3_inv(const t_vec3 v)
{
	t_vec3	res;

		res.x = 1.0 / v.x;
		res.x = 1.0 / v.y;
		res.x = 1.0 / v.z;
	return (res);
}
