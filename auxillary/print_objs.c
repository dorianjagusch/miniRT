/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:15:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 14:16:03 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_obj obj)
{
	ft_printf("Sphere\n");
	ft_printf("Position:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("Radius:\nR:%f\tG:%f\tB:%f\n", obj.radius);
}

void	print_plane(t_obj obj)
{
	ft_printf("Plane\n");
	ft_printf("Position:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
}

void	print_cylinder(t_obj obj)
{
	ft_printf("Cylinder\n");
	ft_printf("Position:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
}

//Needs to be adjust for actual triangle obj
void	print_triangle(t_obj obj)
{
	ft_printf("Triangle\n");
	ft_printf("Position 1:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("Position 2:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("position 3:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("Vertex 1:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("Vertex 2:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
	ft_printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		obj.position.x, obj.position.y, obj.position.z);
}