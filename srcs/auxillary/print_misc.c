/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:07:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/20 18:27:56 by djagusch         ###   ########.fr       */
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

void	print_vec4(t_vec4 vec, char *label)
{
	printf("%s:\tx:%f\ty:%f\tz:%f\tv:%f\n", label, vec.x, vec.y, vec.z, vec.v);
}

void	print_col(t_vec4 vec, char *label)
{
	printf("%s:\tr:%f\tg:%f\tb:%f\n", label, vec.x, vec.y, vec.z);
}

