/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_shader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:08:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 13:39:16 by djagusch         ###   ########.fr       */
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
	//	const t_material	*mat = get_material(hit->material);


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

