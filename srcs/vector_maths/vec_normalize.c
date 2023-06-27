/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:14:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/25 22:15:33 by djagusch         ###   ########.fr       */
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