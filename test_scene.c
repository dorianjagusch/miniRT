/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 14:18:33 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector_math.h"
#include "minirt.h"

t_scene	start_scene(void)
{
	t_scene	scene;

	// Ambient light
	scene.amb.ratio = 0.5;
	scene.amb.colour.x = 200;
	scene.amb.colour.y = 200;
	scene.amb.colour.z = 200;

	// Camera
	scene.cam.pos.x = 0.0;
	scene.cam.pos.y = 0.0;
	scene.cam.pos.z = 10.0;
	scene.cam.forward.x = 0;
	scene.cam.forward.y = 0;
	scene.cam.forward.z = -1;
	scene.cam.right.x = 0;
	scene.cam.right.y = 1;
	scene.cam.right.z = 0;
	scene.cam.fov = 90;

	// Light
	scene.light.pos.x = -10.0;
	scene.light.pos.y = 20.0;
	scene.light.pos.z = 30.0;
	scene.light.ratio = 0.8;
	scene.light.colour.x = 255;
	scene.light.colour.y = 255;
	scene.light.colour.z = 255;

	// Sphere
	scene.n_objs = 1;
	scene.objs = malloc(sizeof(t_obj) * scene.n_objs);

	scene.objs[0].type = 0;
	scene.objs[0].position.x = 5.0;
	scene.objs[0].position.y = 5.0;
	scene.objs[0].position.z = 5.0;
	scene.objs[0].radius = 3.0;
	scene.objs[0].colour.x = 255;
	scene.objs[0].colour.y = 0;
	scene.objs[0].colour.z = 0;
}
