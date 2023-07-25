/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sub_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:32:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"

t_vec3	vec3_sub(const t_vec3 v, const t_vec3 u)
{
	t_vec3	res;

	res.x = v.x - u.x;
	res.y = v.y - u.y;
	res.z = v.z - u.z;
	return (res);
}

t_vec3	vec3_subf(const t_vec3 v, const float val)
{
	t_vec3	res;

	res.x = v.x - val;
	res.y = v.y - val;
	res.z = v.z - val;
	return (res);
}

t_vec4	vec4_sub(const t_vec4 v, const t_vec4 u)
{
	t_vec4	res;

	res.v = 1;
	res.x = v.x - u.x;
	res.y = v.y - u.y;
	res.z = v.z - u.z;
	return (res);
}

t_vec4	vec4_subf(const t_vec4 v, const float val)
{
	t_vec4	res;

	res.v = 1;
	res.x = v.x - val;
	res.y = v.y - val;
	res.z = v.z - val;
	return (res);
}
