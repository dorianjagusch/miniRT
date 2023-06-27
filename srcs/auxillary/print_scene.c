/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:32:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 15:13:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_objs(t_obj obj)
{
	static const t_print_func	printfunc[] = {
	{sphere, &print_sphere},
	{plane, &print_plane},
	{cylinder, &print_cylinder}
	};

	printfunc[obj.type].print_funct(obj);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		obj.colour.x, obj.colour.y, obj.colour.z);
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
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		cam.pos.x, cam.pos.y, cam.pos.z);
	printf("Direction:\nx:%f\ty:%f\tz:%f\n",
		cam.forward.x, cam.forward.y, cam.forward.z);
	printf("Right:\nx:%f\ty:%f\tz:%f\n",
		cam.right.x, cam.right.y, cam.right.z);
	printf("Up:\nx:%f\ty:%f\tz:%f\n",
		cam.up.x, cam.up.y, cam.up.z);
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
		print_objs(scene.objs[i++]);
		printf("--------------------------\n");
	}
	printf("==========================\n");
}
