/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:32:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/21 19:07:09 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef void	(*t_printfunc)(t_object *);

void	print_objs(t_object *obj)
{
	static const t_printfunc	printfunc[] = {
		&print_sphere,
		&print_plane,
		&print_cylinder,
		&print_disk,
		&print_triangle,
		&print_box,
		&print_mesh,
		&print_cone
	};
	printf("type: %d\n", obj->type);
	printfunc[obj->type]((void*)obj);
}

void	print_light(t_light light)
{
	printf("Point light\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		light.pos.x, light.pos.y, light.pos.z);
	printf("Ratio: %f\n", light.ratio);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		light.colour.x, light.colour.y, light.colour.z);
}

void	print_camera(t_camera cam)
{
	printf("Camera\n");
	print_vec3(cam.pos, "Position");
	print_vec3(cam.dir, "Direction");
	print_vec3(cam.right, "Right");
	print_vec3(cam.up, "Up");
	printf("aspect ratio: %f\n", cam.aspect_ratio);
	printf("FOV: %f\n", cam.fov);
}

void	print_scene(t_scene scene)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	printf("========= SCENE ==========\n");
	printf("Ambient light\n");
	//printf("Ratio: %f\n", scene.amb.ratio);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		scene.amb.colour.x, scene.amb.colour.y, scene.amb.colour.z);
	while (num < scene.n_lights)
	{
		printf("--------------------------\n");
		print_light(scene.lights[num]);
		num++;
		printf("--------------------------\n");
	}
	print_camera(scene.cam);
	printf("--------------------------\n");
	while (i < scene.n_objs)
	{
		printf("Object #%d of %d\n", i, scene.n_objs);
		print_objs(scene.objs + i++);
		printf("--------------------------\n");
	}
	printf("==========================\n");
}
