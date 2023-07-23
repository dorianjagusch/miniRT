/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_endian.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:57:21 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 14:57:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_small_endian(void)
{
	int		num;
	char	*byte_ptr;

	num = 1;
	byte_ptr = (char *) &num;
	return ((int)(*byte_ptr));
}
