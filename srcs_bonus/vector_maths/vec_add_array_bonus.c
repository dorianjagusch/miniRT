/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add_array_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:43:37 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/25 11:48:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math_bonus.h"

t_vec4	vec4_add_array(t_vec4 v, const t_vec4 *array, size_t arr_len)
{
	size_t	i;
	t_vec4	res;

	i = 0;
	res = v;
	while (i < arr_len)
	{
		res = vec4_add(res, array[i]);
		i++;
	}
	return (res);

}