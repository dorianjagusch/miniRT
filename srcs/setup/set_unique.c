/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:51:04 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/25 11:57:34 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_camera(t_scene *scene, char **line)
{
	*line += 2;
	scene->cam.pos = get_vec3(line);
	scene->cam.dir = get_vec3(line);
	scene->cam.fov = get_float(line, ANGLE);
	scene->cam.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	vec3_normalize(&scene->cam.dir);
	scene->cam.right = vec3_cross(scene->cam.dir, \
		(t_vec3){0, 1.0f, -10e-2});
	vec3_normalize(&scene->cam.right);
	scene->cam.up = vec3_cross(scene->cam.right, scene->cam.dir);
	vec3_normalize(&scene->cam.up);
	scene->cam.valid = 1;
}

static void	set_ambient(t_scene *scene, char **line)
{
	*line += 2;
	scene->amb.ratio = get_float(line, RATIO);
	scene->amb.colour = get_colour(line);
	scene->amb.valid = 1;
}

void	set_unique(t_scene *scene, char **line)
{
	static int	flag[3];

	if (ft_strncmp("A ", *line, 2) == 0 && !flag[0])
	{
		set_ambient(scene, line);
		flag[0] = 1;
	}
	else if (ft_strncmp("L ", *line, 2) == 0 && flag[1] <= 6)
	{		
		*line += 2;
		scene->lights[flag[1]].pos = get_vec3(line);
		ft_skip_ws(line);
		scene->lights[flag[1]].ratio = get_float(line, RATIO);
		scene->lights[flag[1]].colour = get_colour(line);
		scene->lights[flag[1]].valid = 1;
		scene->n_lights += 1;
		flag[1] += 1;
	}
	else if (ft_strncmp("C ", *line, 2) == 0 && !flag[2])
	{
		set_camera(scene, line);
		flag[2] = 1;
	}
	else
		ft_error(ident_err);
}
