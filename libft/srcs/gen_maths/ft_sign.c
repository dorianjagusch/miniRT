/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 07:03:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 16:57:41 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef EPSILON
# define EPSILON 10e-8
#endif

int	ft_sign(float a)
{
	if (a > 0)
		return (1);
	return (-1);
}
