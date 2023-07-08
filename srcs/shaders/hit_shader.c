/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/08 11:55:16 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "materials.h"

static const t_material	*get_material(t_material_e material_id)
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

	material_id = rubber;
	return (materials[material_id]);
}

t_vec4	hit_shader(const t_scene *scene,
		const t_hitresult *hit, const t_light_info *light_info)
{
	t_vec4				col[5];
	const t_material	*mat = get_material(hit->material);
	float				spec_exp;
	t_vec3			reflected_ray;

	ft_bzero(col, 5 * sizeof(t_vec4));
	col[ambient] = vec4_multf(scene->amb.colour, scene->amb.ratio);
	col[ambient] = vec4_compmult(hit->colour, col[ambient]);
	if (light_info->distance > EPSILON)
	{
		col[diffuse] = vec4_multf(scene->light.colour, scene->light.ratio * 100);
		col[diffuse] = vec4_multf(col[diffuse], light_info->intensity);
		col[diffuse] = vec4_compmult(hit->colour,
				col[diffuse]);
		col[diffuse] = vec4_multf(col[diffuse],
				 1 / (light_info->distance * light_info->distance));
	}
	else
		DEBUG_ONLY(printf("in shadow\n"));
	DEBUG_ONLY(print_col(col[diffuse], "diffuse"));
	reflected_ray = vec3_reflect(vec3_neg(light_info->direction), hit->normal);
	spec_exp = powf(vec3_dot(light_info->direction, reflected_ray),
			mat->specular);
	spec_exp = fmax(spec_exp, 0.0);
	col[specular] = vec4_multf(vec4_compmult((t_vec4){0.6, 0.6, 0.6, 0.6},
				scene->light.colour), spec_exp);
	if (light_info->intensity < EPSILON)
		print_col(hit->colour, "Surface colour");
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
