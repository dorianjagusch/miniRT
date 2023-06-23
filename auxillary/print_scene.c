/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:32:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 14:15:40 by djagusch         ###   ########.fr       */
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
	ft_printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		obj.colour.x, obj.colour.y, obj.colour.z);
}

void	print_light(t_light light)
{
	ft_printf("Point light\n");
	ft_printf("Position:\nx:%f\ty:%f\tz:%f\n",
		light.pos.x, light.pos.y, light.pos.z);
	ft_printf("Ratio: %f\n", light.ratio);
	ft_printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		light.colour.x, light.colour.y, light.colour.z);
}

void	print_camera(t_camera cam)
{
	ft_printf("Camera\n");
	ft_printf("Position:\nx:%f\ty:%f\tz:%f\n",
		cam.pos.x, cam.pos.y, cam.pos.z);
	ft_printf("Direction:\nx:%f\ty:%f\tz:%f\n",
		cam.forward.x, cam.forward.y, cam.forward.z);
	ft_printf("Right:\nx:%f\ty:%f\tz:%f\n",
		cam.right.x, cam.right.y, cam.right.z);
	ft_printf("Up:\nx:%f\ty:%f\tz:%f\n",
		cam.up.x, cam.up.y, cam.up.z);
}

void	print_scene(t_scene scene)
{
	int	i;

	i = 0;
	ft_printf("========= SCENE ==========\n");
	ft_printf("Ambient light\n");
	ft_printf("Ratio: %f\n", scene.amb.ratio);
	ft_printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		scene.amb.colour.x, scene.amb.colour.y, scene.amb.colour.z);
	ft_printf("--------------------------\n");
	print_light(scene.light);
	ft_printf("--------------------------\n");
	print_camera(scene.cam);
	ft_printf("--------------------------\n");
	while (i < scene.n_objs)
		print_object(scene.objs[i++]);
	ft_printf("==========================\n");
}
