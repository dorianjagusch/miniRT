/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_identity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:01:44 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 14:05:05 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4_math.h"

t_mat4	mat4_identity(void)
{
	t_mat4	result;
	int		i;
	int		j;

	i = -1;
	ft_bzero(&result, sizeof(t_mat4));
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				result.data[i][j] = 1.0f;
		}
	}
	return (result);
}
