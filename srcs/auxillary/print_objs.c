/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:15:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/04 15:59:13 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"

void	print_sphere(t_obj obj)
{
	printf("Sphere\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		obj.pos.x, obj.pos.y, obj.pos.z);
	printf("Radius:\n%f\n", obj.radius);
}

void	print_plane(t_obj obj)
{
	printf("Plane\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		obj.pos.x, obj.pos.y, obj.pos.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		obj.normal.x, obj.normal.y, obj.normal.z);
}

void	print_cylinder(t_obj obj)
{
	printf("Cylinder\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		obj.pos.x, obj.pos.y, obj.pos.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		obj.normal.x, obj.normal.y, obj.normal.z);
	printf("Radius:\n%f\n", obj.radius);
	printf("Height:\n%f\n", obj.height);
}
void	print_disk(t_obj obj)
{
	printf("Disk\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		obj.pos.x, obj.pos.y, obj.pos.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		obj.normal.x, obj.normal.y, obj.normal.z);
	printf("Radius:\n%f\n", obj.radius);
}


void	print_ray(t_ray ray)
{
	printf("ray\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		ray.origin.x, ray.origin.y, ray.origin.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		ray.direction.x, ray.direction.y, ray.direction.z);
}

//Needs to be adjust for actual triangle obj
void	print_triangle(t_obj obj)
{
	printf("Triangle\n");
	printf("Position 1:\nx:%f\ty:%f\tz:%f\n",
		obj.tri_point[0].x, obj.tri_point[0].y, obj.tri_point[0].z);
	printf("Position 2:\nx:%f\ty:%f\tz:%f\n",
		obj.tri_point[0].x, obj.tri_point[0].y, obj.tri_point[0].z);
	printf(" 3:\nx:%f\ty:%f\tz:%f\n",
		obj.tri_point[0].x, obj.tri_point[0].y, obj.tri_point[0].z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		obj.normal.x, obj.normal.y, obj.normal.z);
}
