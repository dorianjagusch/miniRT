/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:43:37 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/24 12:19:57 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec4	vec4_add_array(t_vec4 v, const t_vec4 *array, size_t arr_len)
{
	int		i;
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
