/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vmult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:43:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 10:38:58 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include <math.h>

//important: if dot(v, u) > 0 acute angle => suface is tilted toward camera
double vec3_dot(t_vec3 v, t_vec3 u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

double vec3_mag(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
/*the cross product vec3_cross(forward, right) is used to calculate the up vector, which is perpendicular to both the forward and right vectors.
It determines the upward direction relative to the camera's orientation.*/
t_vec3 ft_cross(t_vec3 v, t_vec3 u)
{
	t_vec3	res;

	res.x = v.y * u.z - v.z * u.y;
	res.y = v.x * u.z - v.z * u.x;
	res.z = v.x * u.y - v.y * u.x;
	return (res);
}

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

	res.v = val * v.v;
	res.x = val * v.x;
	res.y = val * v.y;
	res.z = val * v.z;
	return (res);
}
