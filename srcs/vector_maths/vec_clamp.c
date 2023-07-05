/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:56:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 11:08:30 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "libft.h"

void	vec3_clamp(t_vec4 *v, const double min, const double max)
{
	v->x = fminf(fmaxf(v->x, min), max);
	v->y = fminf(fmaxf(v->y, min), max);
	v->z = fminf(fmaxf(v->z, min), max);
}

void	vec4_clamp(t_vec4 *v, const double min, const double max)
{
	v->x = fminf(fmaxf(v->x, min), max);
	v->y = fminf(fmaxf(v->y, min), max);
	v->z = fminf(fmaxf(v->z, min), max);
}
