/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 15:10:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "materials.h"

static const t_material	*get_material(int material_id)
{
	static const t_material	*materials[] = {
		&g_matte_material,
		&g_shiny_material,
		&g_glass_material,
		&g_emissive_material,
		&g_metal_material,
		&g_plastic_material,
		&g_water_material,
		&g_rubber_material,
		&g_mirror_material,
		&g_translucent_material,
		&g_fabric_material,
		&g_concrete_material,
		&g_ice_material,
		&g_translucent_glass_material,
		&g_brushed_metal_material,
		&g_frosted_glass_material,
		&g_marble_material,
		&g_velvet_material,
		&g_ceramic_material,
		&g_paper_material
	};

	return (materials[1]);
}

t_vec4	hit_shader(const t_ray *ray, const t_scene *scene,
		const t_hitresult *hit, const t_light_info *light_info)
{
	static t_vec4		col[5] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};
	const t_material	*mat = get_material(scene->objs[hit->obj_id].material);
	double				spec_exp;
	t_vec3				reflected_ray;

	col[ambient] = vec4_multf(scene->amb.colour, scene->amb.ratio);
	col[ambient] = vec4_compmult(scene->objs[hit->obj_id].colour, col[ambient]);
	if (light_info->distance > EPSILON)
	{
		col[diffuse] = vec4_multf(scene->light.colour, scene->light.ratio * 100);
		col[diffuse] = vec4_multf(col[diffuse], light_info->intensity);
		col[diffuse] = vec4_compmult(scene->objs[hit->obj_id].colour,
				col[diffuse]);
		col[diffuse] = vec4_multf(col[diffuse],
				 1 / (light_info->distance * light_info->distance));
	}
	DEBUG_ONLY(print_col(col[diffuse], "diffuse"));
	// reflected_ray = vec3_reflect(vec3_neg(light_info->direction), hit->normal);
	// spec_exp = powf(vec3_dot(light_info->direction, reflected_ray),
	// 		mat->specular);
	// spec_exp = fmin(fmax(spec_exp, 0.0), 1);
	// col[specular] = vec4_multf(vec4_compmult((t_vec4){0.6, 0.6, 0.6, 0.6},
	// 			scene->light.colour), spec_exp);
	col[final] = vec4_add(vec4_add(col[ambient], col[diffuse]), col[specular]);
	// if (ray->transparency < 1.0)
	// {
	// 	col[transparent] = vec4_multf(col[final], 1.0 - ray->transparency);
	// 	col[final] = vec4_add(vec4_multf(col[final], ray->transparency),
	// 			col[transparent]);
	// }
	return (col[final]);
}
