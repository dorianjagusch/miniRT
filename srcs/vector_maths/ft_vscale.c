/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vscale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:56:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/21 23:06:06 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "libft.h"

void	ft_v3scale(t_vec3 *v, t_range old, t_range new)
{
	(*v).x = ft_scale((*v).x, old, new);
	(*v).y = ft_scale((*v).y, old, new);
	(*v).z = ft_scale((*v).z, old, new);
}


void	ft_v4scale(t_vec4 *v, t_range old, t_range new)
{
	(*v).v = ft_scale((*v).v, old, new);
	(*v).x = ft_scale((*v).x, old, new);
	(*v).y = ft_scale((*v).y, old, new);
	(*v).z = ft_scale((*v).z, old, new);
}
