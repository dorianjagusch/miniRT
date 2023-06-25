/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_reflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 22:14:14 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/25 22:14:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3  vec3_reflect(t_vec3 v, t_vec3 normal)
{
	t_vec3	res;

	res = vec3_add(v, vec3_multf(normal, -2 * vec3_dot(v, normal)));
	return (res);
}
