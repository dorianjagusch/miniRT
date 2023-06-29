/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dotprod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:10 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/29 12:10:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	vec4_dot(t_vec4 v1, t_vec4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
