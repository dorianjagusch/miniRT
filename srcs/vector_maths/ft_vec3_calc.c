/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 18:45:10 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	ft_v3norm(t_vec3 *v) //measure
{
	double	mag;

	mag = sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	(*v).x /= mag;
	(*v).y /= mag;
	(*v).z /= mag;
}

double ft_cos_angle(t_vec3 v, t_vec3 u)
{
	double res;

	res = ft_v3dot(v, u) / (ft_v3mag(v) * ft_v3mag(u));
	return (res);
}

t_vec3 ft_reflect(t_vec3 v, t_vec3 normal)
{
	t_vec3	res;

	res = ft_v3add(v, ft_v3multf(normal, -2 * ft_v3dot(v, normal)));
	return (res);
}
