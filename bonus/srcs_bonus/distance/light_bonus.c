/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:52:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 12:14:14 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"

static t_vec4	specular_colour(const t_scene *scene,
	const t_hitresult *hit, const t_light_info *light_info, int num)
{
	t_vec3	half_vec;
	float	spec_angle;
	t_vec4	colour;
	float	specular;

	half_vec = vec3_add(scene->directions[num], vec3_neg(scene->cam.dir));
	vec3_normalize(&half_vec);
	spec_angle = fmaxf(vec3_dot(hit->normal, half_vec), 0.0f);
	specular = powf(spec_angle, 60); // object specific
	colour = vec4_multf(vec4_multf(light_info->colour, specular * 100),
			1 / (scene->distances[num] * scene->distances[num]));
	return (colour);
}

static void check_shadow(t_scene *scene, t_ray shadowray, \
            t_hitresult *hit, int num)
{
    int i;
    
    i = 0;
    scene->directions[num] = vec3_sub(scene->lights[num].pos, hit->position);
    scene->distances[num] = vec3_mag(scene->directions[num]);
    vec3_normalize(&scene->directions[num]);
    shadowray.direction = scene->directions[num];
    while (i < scene->n_objs)
    {
        if (get_dist(&shadowray, &(scene->objs[i])) < scene->distances[num])
        {
            scene->distances[num] = 0;
            scene->directions[num] = (t_vec3){0, 0, 0};
            i = 0;
            break;
        }
        i++;
    }
}

static void set_specular_and_intensity(t_scene *scene, t_light_info *light_info, \
     t_hitresult *hit)
{
    t_vec4  colour;
    
    colour = (t_vec4){1, 0, 0, 0};
    light_info->intensity = fmax(vec3_dot(hit->normal, \
                        scene->directions[light_info->num])
                        * scene->lights[light_info->num].ratio * 100.0f, 0);
    light_info->intensity /= scene->n_lights;
    colour = vec4_multf(vec4_multf(scene->lights[light_info->num].colour, \
                        light_info->intensity),
                        1.0f / (scene->distances[light_info->num] * 
                        scene->distances[light_info->num]));
    light_info->colour = vec4_add(colour, light_info->colour);
    scene->specular[light_info->num] = specular_colour(scene, hit, \
                        light_info, light_info->num);
}

t_light_info light_distance(t_scene *scene, t_hitresult *hit)
{
    t_ray           shadowray;
    t_light_info    light_info;

    light_info.num = 0;
    ft_bzero(&light_info, sizeof(t_light_info));
    shadowray.origin = hit->position;
    light_info.colour = (t_vec4){1, 0, 0, 0};
    while (light_info.num < scene->n_lights)
    {
        check_shadow(scene, shadowray, hit, light_info.num);
        if (scene->distances[light_info.num] >= EPSILON)
            set_specular_and_intensity(scene, &light_info, hit);
        light_info.num++;
    }
    return (light_info);
}