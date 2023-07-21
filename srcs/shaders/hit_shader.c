/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/21 11:13:41 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	specular_colour(const t_ray *ray, const t_scene *scene,
	const t_hitresult *hit, const t_light_info *light_info)
{
	t_vec3	half_vec;
	float	spec_angle;
	t_vec4	colour;
	float	specular;

	half_vec = vec3_add(light_info->direction, vec3_neg(scene->cam.dir));
	vec3_normalize(&half_vec);
	spec_angle = fmaxf(vec3_dot(hit->normal, half_vec), 0.0f);
	specular = powf(spec_angle, 100);
	colour = vec4_multf(vec4_multf(light_info->colour, specular * 100),
			1 / (light_info->distance * light_info->distance));
	return (colour);
}

t_vec4	hit_shader(const t_ray *ray, const t_scene *scene,
		const t_hitresult *hit, const t_light_info *light_info)
{
	t_vec4				col[5];

	ft_bzero(col, 5 * sizeof(t_vec4));
	col[ambient] = vec4_multf(scene->amb.colour, scene->amb.ratio);
	col[ambient] = vec4_compmult(hit->colour, col[ambient]);
	if (light_info->distance >= EPSILON)
	{
		col[diffuse] = vec4_multf(scene->light.colour, light_info->intensity);
		col[diffuse] = vec4_compmult(hit->colour,
				col[diffuse]);
		col[diffuse] = vec4_multf(col[diffuse],
				1 / (light_info->distance * light_info->distance));
		col[specular] = specular_colour(ray, scene, hit, light_info);
	}
	col[final] = vec4_add(vec4_add(col[ambient], col[diffuse]), col[specular]);
	// if (ray->transparency < 1.0)
	// {
	// 	col[transparent] = vec4_multf(col[final], 1.0 - ray->transparency);
	// 	col[final] = vec4_add(vec4_multf(col[final], ray->transparency),
	// 			col[transparent]);
	// }
	return (col[final]);
}


// t_vec4	hit_shader(const t_scene *scene, const t_payload *payload)
// {
// 	float	intensity;
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
