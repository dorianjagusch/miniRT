/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vmult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:43:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/19 18:29:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include <math.h>

//important: if dot(v, u) > 0 acute angle => suface is tilted toward camera
double ft_v3dot(t_vec3 v, t_vec3 u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

double ft_v3mag(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3 ft_cross(t_vec3 v, t_vec3 u)
{
	t_vec3	res;

	res.x = v.y * u.z - v.z * u.y;
	res.y = v.x * u.z - v.z * u.x;
	res.z = v.x * u.y - v.y * u.x;
	return (res);
}

t_vec3	ft_v3multf(t_vec3 v, double val)
{
	t_vec3	res;

	res.x = val * v.x;
	res.y = val * v.y;
	res.z = val * v.z;
	return (res);
}

t_vec4	ft_v4multf(t_vec4 v, double val)
{
	t_vec4	res;

	res.v = val * v.v;
	res.x = val * v.x;
	res.y = val * v.y;
	res.z = val * v.z;
	return (res);
}
