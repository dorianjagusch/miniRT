/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_isnan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:02:10 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/29 12:10:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

int	vec3_isnan(t_vec3 v)
{
    return isnan(v.x) || isnan(v.y) || isnan(v.z);
}

int	vec4_isnan(t_vec4 v)
{
    return isnan(v.x) || isnan(v.y) || isnan(v.z) || isnan(v.v);
}
