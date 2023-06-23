/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 10:38:58 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	hit_shader(t_scene *scene, t_payload *payload)
{
	double	intensity;
	t_vec4	colour;

	intensity = vec3_dot(scene->light.pos, payload->light_dir);
	colour = vec4_multf((scene->objs[payload->obj_id]).colour, intensity);
	return (colour);
}