/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_isnan_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:10 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:32:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"

int	vec3_isnan(const t_vec3 v)
{
	return (isnan(v.x) || isnan(v.y) || isnan(v.z));
}
int	vec3_isinf(const t_vec3 v)
{
	return (isinf(v.x) || isinf(v.y) || isinf(v.z));
}

int	vec4_isnan(const t_vec4 v)
{
	return (isnan(v.x) || isnan(v.y) || isnan(v.z) || isnan(v.v));
}
