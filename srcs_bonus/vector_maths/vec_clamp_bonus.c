/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clamp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:56:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 20:16:55 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include "libft_bonus.h"

void	vec4_clamp(t_vec4 *v, const float min, const float max)
{
	float	overflow;
	int		i;

	i = 0;
	overflow = 0;
	if (v->x - max > 0)
		overflow += v->x - max;
	if (v->y - max > 0)
		overflow += v->y - max;
	if (v->z - max > 0)
		overflow += v->z - max;
	vec4_addf(*v, overflow);
	v->x = fminf(fmaxf(v->x, min), max);
	v->y = fminf(fmaxf(v->y, min), max);
	v->z = fminf(fmaxf(v->z, min), max);
}
