/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 14:12:59 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	hit_shader(t_scene *scene, t_payload *payload)
{
	double	intensity;
	t_vec4	col;

	DEBUG_ONLY(printf("\nlight_dist: %f\n", payload->light_dist));
	DEBUG_ONLY(print_vec3(payload->light_dir, "light_dir"));

	if (payload->light_dist > 0)
	{
		payload->hitnorm = vec3_multf(payload->hitnorm, -1);
		DEBUG_ONLY(print_vec3(payload->hitnorm, "hitnorm"));
		
		intensity = vec3_dot(payload->light_dir, payload->hitnorm);
		DEBUG_ONLY(printf("intensity: %f\n", intensity));
		intensity = fminf(fmaxf(intensity, 0.0), 1.0);
		DEBUG_ONLY(printf("intensity: %f\n", intensity));
		
		col = vec4_multf(scene->light.colour, intensity);
		DEBUG_ONLY(print_vec4(col, "col in shader"));
		
		col = vec4_compmult(scene->objs[payload->obj_id].colour, col);
		DEBUG_ONLY(print_vec4(col, "col in shader"));
	}
	return (col);
}
