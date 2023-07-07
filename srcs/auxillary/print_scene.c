/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:32:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 10:32:46 by djagusch         ###   ########.fr       */
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
		&print_triangle
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

	i = 0;
	printf("========= SCENE ==========\n");
	printf("Ambient light\n");
	printf("Ratio: %f\n", scene.amb.ratio);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		scene.amb.colour.x, scene.amb.colour.y, scene.amb.colour.z);
	printf("--------------------------\n");
	print_light(scene.light);
	printf("--------------------------\n");
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
