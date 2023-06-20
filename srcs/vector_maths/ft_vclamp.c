/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vclamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:56:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/20 23:02:12 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

void	ft_v3clamp(t_vec4 *v, double low, double high)
{
	(*v).x = ft_max(ft_min(x, high), low);
	(*v).y = ft_max(ft_min(y, high), low);
	(*v).z = ft_max(ft_min(z, high), low);
}

void	ft_v4clamp(t_vec4 *v, double low, double high)
{
	(*v).v = ft_max(ft_min(v, high), low);
	(*v).x = ft_max(ft_min(x, high), low);
	(*v).y = ft_max(ft_min(y, high), low);
	(*v).z = ft_max(ft_min(z, high), low);
}