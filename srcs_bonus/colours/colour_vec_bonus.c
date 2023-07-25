/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_vec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:28:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 11:32:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"
#include "minirt_bonus.h"

int32_t	vec4_toint32(t_vec4 colour)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;

	int32_t t = 1; // transperancy was setting to negative number?
	r = 255 * colour.x;
	g = 255 * colour.y;
	b = 255 * colour.z;
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

t_vec4	ft_int32tov4(int32_t colour)
{
	t_vec4	result;

	result.v = 1;
	result.x = get_r(colour);
	result.y = get_g(colour);
	result.z = get_b(colour);
	return (result);
}

t_vec4	ft_inttov4(int colour)
{
	t_vec4	result;

	result.v = 1;
	result.x = (float)((colour >> 16) & 0xFF);
	result.y = (float)((colour >> 8) & 0xFF);
	result.z = (float)(colour & 0xFF);
	return (result);
}

t_vec4	ft_trgbtov4(int colour[4])
{
	t_vec4	result;

	result.v = 1;
	result.x = (float) colour[1];
	result.y = (float) colour[2];
	result.z = (float) colour[3];
	return (result);
}

void	ft_rgbtonorm(t_vec4 *colour)
{
	colour->v = 1;
	colour->x /= 255.0;
	colour->y /= 255.0;
	colour->z /= 255.0;
}
