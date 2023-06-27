/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:12:26 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 13:16:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

double	vec3_mag(t_vec3 v)
{
	double	div;

	div = sqrt(vec3_dot(v, v));
	v.x /= div;
	v.y /= div;
	v.z /= div;
}

double	vec4_mag(t_vec4 v)
{
	double	div;

	div = sqrt(vec4_dot(v, v));
	v.v /= div;
	v.x /= div;
	v.y /= div;
	v.z /= div;
}
