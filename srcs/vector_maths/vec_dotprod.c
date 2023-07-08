/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dotprod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:10 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 15:53:12 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

float	vec3_dot(const t_vec3 v1, const t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	vec4_dot(const t_vec4 v1, const t_vec4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
