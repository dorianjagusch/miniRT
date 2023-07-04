/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_neg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:59:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/04 12:01:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vector_math.h"

t_vec3	vecc_neg(t_vec3 v)
{
	t_vec3	w;

	w.x = -v.x;
	w.y = -v.y;
	w.z = -v.z;
	return (w);
}
