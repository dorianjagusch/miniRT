/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 17:50:25 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	hit_shader(t_scene *scene, t_payload *payload)
{
	double	intensity;
	t_vec4	light_col;
	t_vec4	colour;
	t_vec4	col;

	DEBUG_ONLY(printf("\nlight_dist: %f\n", payload->light_dist));
	DEBUG_ONLY(print_vec3(payload->light_dir, "light_dir"));
	// colour = vec4_compmult(scene->objs[payload->obj_id].colour,
	// 		vec4_multf(scene->amb.colour, scene->amb.ratio));
	col = (t_vec4){1, 0, 0, 0};
	if (payload->light_dist > 0)
	{
		DEBUG_ONLY(print_vec3(payload->hitnorm, "hitnorm"));

		intensity = fmax(vec3_dot(payload->light_dir, payload->hitnorm), 0);
		DEBUG_ONLY(printf("intensity: %f\n", intensity));

		col = vec4_multf(scene->light.colour, intensity * scene->light.ratio);
		DEBUG_ONLY(print_vec4(col, "col in shader"));

		col = vec4_compmult(scene->objs[payload->obj_id].colour, col);
		DEBUG_ONLY(print_vec4(col, "col in shader"));
		// light_col = vec4_multf(scene->light.colour, intensity);
        // DEBUG_ONLY(print_vec4(col, "light_col"));
        // col = vec4_compmult((scene->objs[payload->obj_id]).colour, light_col);
        //printf("Object col:\nr:%f g:%f, b%f\n", scene->objs[payload->obj_id].col.x, scene->objs[payload->obj_id].col.y, scene->objs[payload->obj_id].col.z);
	}
	return (col);
}
