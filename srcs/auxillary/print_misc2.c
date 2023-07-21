/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_misc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:07:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/21 13:31:36 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "scene.h"
#include "print_helpers.h"
#include "shaders.h"

void	print_light_info(t_light_info light_info)
{
	printf("Light Info:\n----------------------------\n");
	print_vec3(light_info.direction, "Direction");
	printf("Distance: %f\n", light_info.distance);
	printf("Intensity: %f\n", light_info.intensity);
	printf("----------------------------\n");
}
