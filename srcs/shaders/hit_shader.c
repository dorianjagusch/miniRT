/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/26 22:32:34 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	hit_shader(t_scene *scene, t_payload *payload)
{
	double	intensity;
	t_vec4	colour;

	if (payload->light_dist > 0)
		payload->hitnorm = vec3_multf(payload->hitnorm, -1);
		intensity = vec3_dot(payload->light_dir, payload->hitnorm);
		//printf("instensity %f\n", intensity);
		colour = vec4_multf((scene->objs[payload->obj_id]).colour, intensity);
		//printf("Object colour:\nr:%f g:%f, b%f\n", scene->objs[payload->obj_id].colour.x, scene->objs[payload->obj_id].colour.y, scene->objs[payload->obj_id].colour.z);
	return (colour);
}
