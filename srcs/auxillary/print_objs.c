/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:15:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 10:15:52 by djagusch         ###   ########.fr       */
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

//Needs to be adjusted for actual triangle obj
void	print_triangle(t_object *obj)
{
	t_triangle	*triangle;

	triangle = &obj->triangle;
	printf("Triangle\n");
	printf("Vertex 1:\nx:%f\ty:%f\tz:%f\n",
		triangle->verts[0].x, triangle->verts[0].y, triangle->verts[0].z);
	printf("Vertex 2:\nx:%f\ty:%f\tz:%f\n",
		triangle->verts[1].x, triangle->verts[1].y, triangle->verts[1].z);
	printf("Vertex 3:\nx:%f\ty:%f\tz:%f\n",
		triangle->verts[2].x, triangle->verts[2].y, triangle->verts[2].z);
	// printf("Normal:\nx:%f\ty:%f\tz:%f\n",
	// 	triangle->verts.x, triangle->verts.y, triangle->verts.z);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		triangle->colour.x, triangle->colour.y, triangle->colour.z);
}

void	print_box(t_object *obj)
{
	t_box	*box;

	box = &obj->box;
	printf("Box\n");
	printf("Vertex 1:\nx:%f\ty:%f\tz:%f\n",
		box->verts[0].x, box->verts[0].y, box->verts[0].z);
	printf("Vertex 2:\nx:%f\ty:%f\tz:%f\n",
		box->verts[1].x, box->verts[1].y, box->verts[1].z);
	// printf("Normal:\nx:%f\ty:%f\tz:%f\n",
	// 	box->verts.x, box->verts.y, box->verts.z);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		box->colour.x, box->colour.y, box->colour.z);
}
