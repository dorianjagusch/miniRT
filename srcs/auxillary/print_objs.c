/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:15:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 13:12:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//Needs to be adjusted for actual triangle obj
void	print_triangle(t_object *obj)
{
	t_triangle	*triangle;

	triangle = &obj->triangle;
	printf("Triangle\n");
	printf("Position 1:\nx:%f\ty:%f\tz:%f\n",
		triangle->tri_point[0].x, triangle->tri_point[0].y, triangle->tri_point[0].z);
	printf("Position 2:\nx:%f\ty:%f\tz:%f\n",
		triangle->tri_point[1].x, triangle->tri_point[1].y, triangle->tri_point[1].z);
	printf("postition 3:\nx:%f\ty:%f\tz:%f\n",
		triangle->tri_point[2].x, triangle->tri_point[2].y, triangle->tri_point[2].z);
	// printf("Normal:\nx:%f\ty:%f\tz:%f\n",
	// 	triangle->normal.x, triangle->normal.y, triangle->normal.z);
}

void	print_mesh(t_object *obj)
{
	t_mesh	*mesh;
	int		count;

	count = 0;
	mesh = &obj->mesh;

	printf("Mesh\n");
	printf("number of triangles: %f\n", mesh->n_triangles);
	while (count < mesh->n_triangles)
	{

		printf("Triangle %d\n", count);
		printf("Position 1:\nx:%f\ty:%f\tz:%f\n",
			mesh->triangle_data[count].triangle.tri_point[0].x, mesh->triangle_data[count].triangle.tri_point[0].y, mesh->triangle_data[count].triangle.tri_point[0].z);
		printf("Position 2:\nx:%f\ty:%f\tz:%f\n",
			mesh->triangle_data[count].triangle.tri_point[1].x, mesh->triangle_data[count].triangle.tri_point[1].y, mesh->triangle_data[count].triangle.tri_point[1].z);
		printf("postition 3:\nx:%f\ty:%f\tz:%f\n",
			mesh->triangle_data[count].triangle.tri_point[2].x, mesh->triangle_data[count].triangle.tri_point[2].y, mesh->triangle_data[count].triangle.tri_point[2].z);
		count++;
	}
}

void	print_cone(t_object *obj)
{
	t_cone	*cone;

	cone = &obj->cone;
	printf("cone\n");
	printf("Position:\nx:%f\ty:%f\tz:%f\n",
		cone->pos.x, cone->pos.y, cone->pos.z);
	printf("Normal:\nx:%f\ty:%f\tz:%f\n",
		cone->normal.x, cone->normal.y, cone->normal.z);
	printf("vertex:\nx:%f\ty:%f\tz:%f\n",
		cone->pos.x, cone->pos.y, cone->pos.z);
	printf("Radius:\n%f\n", cone->radius);
	printf("Height:\n%f\n", cone->height);
	printf("Colour:\nR:%f\tG:%f\tB:%f\n",
		cone->colour.x, cone->colour.y, cone->colour.z);
}

