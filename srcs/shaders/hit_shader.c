/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/04 11:13:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_vec4	hit_shader(const t_scene *scene, const t_payload *payload)
{
	t_vec4	ambient;
	t_vec4	colour;
	double	intensity;
	double	specularity;
	t_vec4	specular;

	colour = (t_vec4){1, 0, 0, 0};
	specularity = 0.9;
	if (EPSILON < payload->light_dist && payload->light_dist < DBL_MAX)
	{
		ambient = vec4_multf(scene->amb.colour, scene->amb.ratio);
		colour = vec4_compmult(scene->objs[payload->obj_id].colour, ambient);
		intensity = vec3_dot(payload->hitnorm, payload->light_dir);
		intensity *= scene->light.ratio / powf(payload->light_dist, 2) * 100; //hackky for distance. Otherwise far too dark
		colour = vec4_multf(colour, intensity);
		//colour = vec4_add (colour, calulcate_specular());
	}
	return (colour);
}


// t_vec4	hit_shader(const t_scene *scene, const t_payload *payload)
// {
// 	double	intensity;
// 	t_vec4	light_col;
// 	t_vec4	colour;
// 	t_vec4	col;

// 	if (payload->light_dist > 0)
// 	{
// 		assert(!vec3_isnan(payload->hitnorm));

// 		intensity = fmax(vec3_dot(payload->light_dir, payload->hitnorm), 0);

// 		col = vec4_multf(scene->light.colour, intensity * scene->light.ratio);

// 		col = vec4_compmult(scene->objs[payload->obj_id].colour, col);
// 		// light_col = vec4_multf(scene->light.colour, intensity);
//         // col = vec4_compmult((scene->objs[payload->obj_id]).colour, light_col);
//         //printf("Object col:\nr:%f g:%f, b%f\n", scene->objs[payload->obj_id].col.x, scene->objs[payload->obj_id].col.y, scene->objs[payload->obj_id].col.z);
// 	}
// 	return (col);
// }
