/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:28:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/21 00:03:08 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "minirt.h"

int32_t	ft_v4toint32(t_vec4 colour)
{
	int32_t r;
	int32_t g;
	int32_t b;

	r = 255 * colour.x;
	g = 255 * colour.y;
	b = 255 * colour.z;

	return ((255 << 24) | (r << 16) | (g << 8) | b);
}

int32_t	ft_rgbtonorm(t_vec4 *colour)
{
	colour->v /= 255.0;
	colour->x /= 255.0;
	colour->y /= 255.0;
	colour->z /= 255.0;
}