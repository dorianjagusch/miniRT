/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/22 13:43:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3	ft_v3add(t_vec3 v, t_vec3 u)
{
	t_vec3	res;

	res.x = v.x + u.x;
	res.y = v.y + u.y;
	res.z = v.z + u.z;
	return (res);
}

t_vec3	ft_v3addf(t_vec3 v, double val)
{
	t_vec3	res;

	res.x = v.x + val;
	res.y = v.y + val;
	res.z = v.z + val;
	return (res);
}

t_vec4	ft_v4add(t_vec4 v, t_vec4 u)
{
	t_vec4	res;

	res.v = v.v + u.v;
	res.x = v.x + u.x;
	res.y = v.y + u.y;
	res.z = v.z + u.z;
	return (res);
}

t_vec4	ft_v4addf(t_vec4 v, double val)
{
	t_vec4	res;

	res.v = v.v + val;
	res.x = v.x + val;
	res.y = v.y + val;
	res.z = v.z + val;
	return (res);
}
