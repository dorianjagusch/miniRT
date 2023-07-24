/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:bonus/srcs_bonus/vector_maths/vec_crossprod_bonus.c
/*   vec_crossprod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:09:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 13:39:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3	vec3_cross(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (result);
=======
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
>>>>>>> textures:libft/srcs/gen_maths/ft_small_endian.c
}
