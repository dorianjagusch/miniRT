/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:15:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 13:14:50 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"

void	print_sphere(t_object *obj)
{
	t_sphere	*sphere;

	sphere = &obj->sphere;
	printf("Sphere\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		sphere->pos.x, sphere->pos.y, sphere->pos.z);
	printf("Radius:\n%f\n", sphere->radius);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		sphere->colour.x, sphere->colour.y, sphere->colour.z);
}

void	print_plane(t_object *obj)
{
	t_plane	*plane;

	plane = &obj->plane;
	printf("Plane\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		plane->pos.x, plane->pos.y, plane->pos.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		plane->normal.x, plane->normal.y, plane->normal.z);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		plane->colour.x, plane->colour.y, plane->colour.z);
}

void	print_cylinder(t_object *obj)
{
	t_cylinder	*cylinder;

	cylinder = &obj->cylinder;
	printf("Cylinder\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		cylinder->pos.x, cylinder->pos.y, cylinder->pos.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		cylinder->normal.x, cylinder->normal.y, cylinder->normal.z);
	printf("Radius:\n%f\n", cylinder->radius);
	printf("Height:\n%f\n", cylinder->height);
	print_disk(obj->cylinder.bottom);
	print_disk(obj->cylinder.top);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		cylinder->colour.x, cylinder->colour.y, cylinder->colour.z);
}

void	print_disk(t_object *obj)
{
	t_disk	*disk;

	disk = &obj->disk;
	printf("Disk\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		disk->pos.x, disk->pos.y, disk->pos.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		disk->normal.x, disk->normal.y, disk->normal.z);
	printf("Radius:\n%f\n", disk->radius);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		disk->colour.x, disk->colour.y, disk->colour.z);
}


void	print_ray(t_ray ray)
{
	printf("ray\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		ray.origin.x, ray.origin.y, ray.origin.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		ray.direction.x, ray.direction.y, ray.direction.z);
}

