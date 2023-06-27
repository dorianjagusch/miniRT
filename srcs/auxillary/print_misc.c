/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:07:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 14:14:37 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "scene.h"
#include "print_helpers.h"
#include "shaders.h"

void	print_vec3(t_vec3 vec, char *label)
{
	printf("%s:\tx:%f\ty:%f\tz:%f\n", label, vec.x, vec.y, vec.z);
}

void	print_col(t_vec4 vec)
{
	printf("Colour\tx:%f\ty:%f\tz:%f\n", vec.x, vec.y, vec.z);
}