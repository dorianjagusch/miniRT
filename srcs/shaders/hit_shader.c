/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/04 17:04:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	hit_shader(const t_scene *scene, const t_payload *payload)
{
	double	ambient;
	double	intensity;
	t_vec4	light_col;
	t_vec4	diffuse_colour;
	t_vec4	colour;

	colour = vec4_multf(scene->amb.colour, scene->amb.ratio);
	if (payload->light_dist > 0)
	{
		intensity = fmax(vec3_dot(payload->hitnorm, payload->light_dir), 0);
		light_col = vec4_multf(scene->light.colour, intensity / (4 * M_PI * \
				payload->light_dist * payload->light_dist * 100));
		colour = vec4_compmult(scene->objs[payload->obj_id].colour,
			light_col);
	}
	return (colour);
}


// hitColor = hitObject->albedo / M_PI * light->intensity * light->color * std::max(0.f, hitNormal.dotProduct(L));