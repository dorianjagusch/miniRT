/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:43:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 10:42:23 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include <math.h>

t_vec3	vec3_multf(t_vec3 v, double val)
{
	t_vec3	res;

	res.x = val * v.x;
	res.y = val * v.y;
	res.z = val * v.z;
	return (res);
}

t_vec4	vec4_multf(t_vec4 v, double val)
{
	t_vec4	res;

	res.v = 1;
	res.x = val * v.x;
	res.y = val * v.y;
	res.z = val * v.z;
	return (res);
}

t_vec3	vec3_compmult(t_vec3 v, t_vec3 u)
{
	t_vec3	res;

	res.x = v.x * u.x;
	res.y = v.y * u.y;
	res.z = v.z * u.z;
	return (res);
}

t_vec4	vec4_compmult(t_vec4 v, t_vec4 u)
{
	t_vec4	res;

	res.v = 1;
	res.x = v.x * u.x;
	res.y = v.y * u.y;
	res.z = v.z * u.z;
	return (res);
}
