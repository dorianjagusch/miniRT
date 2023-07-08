/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:14:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/08 09:09:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

typedef struct s_material
{
	double	diffuse;
	double	specular;
	double	transparency;
	double	refraction;
	double	absorption;
	double	emission;
	double	roughness;
	double	anisotropy;
}			t_material;

typedef enum e_material
{
	matte,
	shiny,
	glass,
	emissive,
	metal,
	plastic,
	water,
	wood,
	rubber,
	mirror,
	translucent,
	fabric,
	concrete,
	ice,
	translucent_glass,
	brushed_metal,
	frosted_glass,
	marble,
	velvet,
	ceramic,
	paper,
}	t_material_e;

static const t_material	g_matte_material = {
	.diffuse = 1.0, //matteness
	.specular = 0.0, //shinyness
	.transparency = 0.0,
	.refraction = 1.0,	//refractive index going from one material to another
	.absorption = 0.0, //kinda like brightness
	.emission = 0.0, //shining (not shiny) material
	.roughness = 1.0, // describes how rough material is
	.anisotropy = 0. //directional influences (like metal ball with lines from machine production)
};

static const t_material	g_shiny_material = {
	.diffuse = 1,
	.specular = 0.9,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.0,
	.anisotropy = 0.0
};

static const t_material	g_glass_material = {
	.diffuse = 0.0,
	.specular = 0.8,
	.transparency = 1.0,
	.refraction = 1.5,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.1,
	.anisotropy = 0.0
};

static const t_material	g_emissive_material = {
	.diffuse = 0.0,
	.specular = 0.0,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 1.0,
	.roughness = 0.0,
	.anisotropy = 0.0
};

static const t_material	g_metal_material = {
	.diffuse = 0.0,
	.specular = 0.9,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.05,
	.anisotropy = 0.0
};

static const t_material	g_plastic_material = {
	.diffuse = 0.8,
	.specular = 0.2,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.5,
	.anisotropy = 0.0
};

static const t_material	g_water_material = {
	.diffuse = 0.0,
	.specular = 0.2,
	.transparency = 0.8,
	.refraction = 1.33,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.1,
	.anisotropy = 0.0
};

static const t_material	g_wood_material = {
	.diffuse = 0.6,
	.specular = 0.1,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.7,
	.anisotropy = 0.3
};

static const t_material	g_rubber_material = {
	.diffuse = 0.7,
	.specular = 0.1,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.9,
	.anisotropy = 0.0
};

static const t_material	g_mirror_material = {
	.diffuse = 0.0,
	.specular = 1.0,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.01,
	.anisotropy = 0.0
};

static const t_material	g_translucent_material = {
	.diffuse = 0.2,
	.specular = 0.1,
	.transparency = 0.5,
	.refraction = 1.33,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.2,
	.anisotropy = 0.0
};

static const t_material	g_fabric_material = {
	.diffuse = 0.8,
	.specular = 0.1,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.4,
	.anisotropy = 0.0
};

static const t_material	g_concrete_material = {
	.diffuse = 0.6,
	.specular = 0.1,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.8,
	.anisotropy = 0.0
};

static const t_material	g_gem_material = {
	.diffuse = 0.1,
	.specular = 0.9,
	.transparency = 0.8,
	.refraction = 2.42,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.05,
	.anisotropy = 0.0
};

static const t_material	g_skin_material = {
	.diffuse = 0.8,
	.specular = 0.2,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.3,
	.anisotropy = 0.0
};

static const t_material	g_ice_material = {
	.diffuse = 0.1,
	.specular = 0.4,
	.transparency = 0.9,
	.refraction = 1.31,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.1,
	.anisotropy = 0.0
};

static const t_material	g_translucent_glass_material = {
	.diffuse = 0.0,
	.specular = 0.2,
	.transparency = 0.8,
	.refraction = 1.5,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.05,
	.anisotropy = 0.0
};

static const t_material	g_brushed_metal_material = {
	.diffuse = 0.3,
	.specular = 0.7,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.8,
	.anisotropy = 0.9
};

static const t_material	g_frosted_glass_material = {
	.diffuse = 0.1,
	.specular = 0.3,
	.transparency = 0.9,
	.refraction = 1.5,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.4,
	.anisotropy = 0.0
};

static const t_material	g_marble_material = {
	.diffuse = 0.5,
	.specular = 0.3,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.2,
	.anisotropy = 0.0
};

static const t_material	g_velvet_material = {
	.diffuse = 0.9,
	.specular = 0.1,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.95,
	.anisotropy = 0.0
};

static const t_material	g_ceramic_material = {
	.diffuse = 0.7,
	.specular = 0.3,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.6,
	.anisotropy = 0.0
};

static const t_material	g_foliage_material = {
	.diffuse = 0.8,
	.specular = 0.2,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.2,
	.anisotropy = 0.0
};

static const t_material	g_gold_material = {
	.diffuse = 0.0,
	.specular = 0.9,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.05,
	.anisotropy = 0.0
};

static const t_material	g_leather_material = {
	.diffuse = 0.7,
	.specular = 0.1,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.8,
	.anisotropy = 0.0
};

static const t_material	g_paper_material = {
	.diffuse = 0.9,
	.specular = 0.1,
	.transparency = 0.0,
	.refraction = 1.0,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.3,
	.anisotropy = 0.0
};

static const t_material	g_plastic_film_material = {
	.diffuse = 0.1,
	.specular = 0.3,
	.transparency = 0.8,
	.refraction = 1.33,
	.absorption = 0.0,
	.emission = 0.0,
	.roughness = 0.1,
	.anisotropy = 0.0
};

#endif