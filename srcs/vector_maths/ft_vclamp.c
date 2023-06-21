/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vclamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:56:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/21 22:39:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "libft.h"

void	ft_v3cscale(t_vec4 *v, double min, double max)
{
	v->x = ft_min(ft_max(v->x, min), max);
	v->y = ft_min(ft_max(v->y, min), max);
	v->z = ft_min(ft_max(v->z, min), max);
}

void	ft_v4clamp(t_vec4 *v, double min, double max)
{
	v->v = ft_min(ft_max(v->v, min), max);
	v->x = ft_min(ft_max(v->x, min), max);
	v->y = ft_min(ft_max(v->y, min), max);
	v->z = ft_min(ft_max(v->z, min), max);
}