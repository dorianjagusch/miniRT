/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 15:13:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	hit_shader(t_scene *scene, t_payload *payload)
{
	double	diffuse_ref;
	t_vec4	light_col;
	t_vec4	col;

	if (payload->light_dist > 0)
	{
		diffuse_ref = vec3_dot(payload->light_dir, payload->hitnorm);
		light_col = vec4_multf(scene->light.colour, diffuse_ref);
		//print_col(light_col);
		col = vec4_compmult((scene->objs[payload->obj_id]).colour, light_col);
		//printf("Object col:\nr:%f g:%f, b%f\n", scene->objs[payload->obj_id].col.x, scene->objs[payload->obj_id].col.y, scene->objs[payload->obj_id].col.z);
	}
	return (col);
}
