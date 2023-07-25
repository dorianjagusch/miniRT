/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_visibility_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:36:39 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 17:19:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"
#include <stdio.h>

int	is_light_visible(const t_vec3 cam_pos, const t_vec3 light_pos,
	const t_vec3 pos, t_vec3 *normal)
{
	float	side1;
	float	side2;
	t_vec3	normal_light;

	side1 = vec3_dot(vec3_sub(cam_pos, pos), *normal);
	normal_light = vec3_sub(light_pos, pos);
	side2 = vec3_dot(normal_light, *normal);
	if ((side1 < EPSILON && side2 < EPSILON)
		|| (side1 > EPSILON && side2 > EPSILON))
	{
		if (side1 < EPSILON && side2 < EPSILON)
			*normal = vec3_neg(*normal);
		return (1);
	}
	if (side1 < EPSILON)
	{
		*normal = vec3_neg(*normal);
		return (1);
	}
	return (0);
}

static void	cap_visibility(t_cylinder *cylinder, t_camera *cam, t_light *light)
{
	cylinder->top->disk.isvisible = is_light_visible(
			cam->pos,
			light->pos,
			cylinder->top->disk.pos,
			&(cylinder->top->disk.normal));
	cylinder->bottom->disk.isvisible = is_light_visible(
			cam->pos,
			light->pos,
			cylinder->bottom->disk.pos,
			&(cylinder->bottom->disk.normal));
	cylinder->bottom->disk.isvisible = cylinder->bottom->disk.isvisible;
}

void	check_visibility(t_scene *scene, int id)
{
	if (scene->objs[id].type == plane_obj)
	{
		scene->objs[id].plane.isvisible = is_light_visible(scene->cam.pos,
				scene->objs[id].plane.pos, scene->objs[id].plane.pos,
				&scene->objs[id].plane.normal);
	}
	if (scene->objs[id].type == disk_obj)
		scene->objs[id].disk.isvisible = is_light_visible(scene->cam.pos,
				scene->objs[id].plane.pos, scene->objs[id].disk.pos,
				&scene->objs[id].disk.normal);
	if (scene->objs[id].type == cylinder_obj)
		cap_visibility(&scene->objs[id].cylinder, &scene->cam, scene->lights);
}
