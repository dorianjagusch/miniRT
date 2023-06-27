/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:28:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 11:38:17 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "minirt.h"

int32_t	vec4_toint32(t_vec4 colour)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;

	r = 255 * colour.x;
	g = 255 * colour.y;
	b = 255 * colour.z;
	return ((255 << 24) | (r << 16) | (g << 8) | b);
}

t_vec4	ft_int32tov4(int32_t colour)
{
	t_vec4	result;

	result.v = get_t(colour);
	result.x = get_r(colour);
	result.y = get_g(colour);
	result.z = get_b(colour);
	return (result);
}

t_vec4	ft_trgbtov4(int colour[4])
{
	t_vec4	result;

	result.v = 1;
	result.x = (double) colour[1];
	result.y = (double) colour[2];
	result.z = (double) colour[3];
	return (result);
}

void	ft_rgbtonorm(t_vec4 *colour)
{
	colour->v /= 255.0;
	colour->x /= 255.0;
	colour->y /= 255.0;
	colour->z /= 255.0;
}
