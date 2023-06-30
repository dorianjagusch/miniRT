/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:12:26 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/29 07:40:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

double	vec3_mag(t_vec3 v)
{
	double	val;

	val = sqrt(vec3_dot(v, v));

	return val;
}

double	vec4_mag(t_vec4 v)
{
	double	val;

	val = sqrt(vec4_dot(v, v));

	return val;
}
