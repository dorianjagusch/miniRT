/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:14:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:32:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include <math.h>

//euclidean norm formula (sqrt(x^2 + y^2 + z^2))
// Normalizes the direction vector of a ray, ensuring its length is equal to 1.0.
void	vec3_normalize(t_vec3 *v) //measure performance and compare to finvsqrt
{
	float	mag;

	mag = sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	v->x /= mag;
	v->y /= mag;
	v->z /= mag;
}

void	vec2_normalize(t_vec2 *v) //measure performance and compare to finvsqrt
{
	float	mag;

	mag = sqrtf((v->x * v->x) + (v->y * v->y));
	v->x /= mag;
	v->y /= mag;
}
