/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 11:34:39 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include <math.h>

//euclidean norm formula (sqrt(x^2 + y^2 + z^2))
// Normalizes the direction vector of a ray, ensuring its length is equal to 1.0.
void	vec3_normalize(t_vec3 *v) //measure performance and compare to finvsqrt
{
	double	mag;

	mag = sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	v->x /= mag;
	v->y /= mag;
	v->z /= mag;
}

double ft_cos_angle(t_vec3 v, t_vec3 u)
{
	double res;

	res = vec3_dot(v, u) / (vec3_mag(v) * vec3_mag(u));
	return (res);
}

t_vec3 vec3_reflect(t_vec3 v, t_vec3 normal)
{
	t_vec3	res;

	res = vec3_add(v, vec3_multf(normal, -2 * vec3_dot(v, normal)));
	return (res);
}
