/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bonus_objs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:45:42 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/17 22:45:14 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_triangle(t_triangle *triangle, char *line)
{
	triangle->type = triangle_obj;
	line += 3;
	triangle->tri_point[0] = get_vec3(&line);
	ft_skip_ws(&line);
	triangle->tri_point[1] = get_vec3(&line);
	ft_skip_ws(&line);
	triangle->tri_point[2] = get_vec3(&line);
	ft_skip_ws(&line);
	triangle->colour = get_colour(&line);
	triangle->edges[0] = vec3_sub(triangle->tri_point[1],
			triangle->tri_point[0]);
	triangle->edges[1] = vec3_sub(triangle->tri_point[2],
			triangle->tri_point[0]);
}

void	create_box(t_box *box, char *line)
{
	box->type = box_obj;
	line += 3;
	box->verts[0] = get_vec3(&line);
	ft_skip_ws(&line);
	box->verts[1] = get_vec3(&line);
	ft_skip_ws(&line);
	box->colour = get_colour(&line);
}

void	create_disk(t_disk *disk, char *line)
{
	disk->type = disk_obj;
	line += 3;
	disk->pos = get_vec3(&line);
	ft_skip_ws(&line);
	disk->normal = get_vec3(&line);
	vec3_normalize(&disk->normal);
	ft_skip_ws(&line);
	disk->radius = get_float(&line, REAL) / 2;
	ft_skip_ws(&line);
	disk->colour = get_colour(&line);
	disk->d = -vec3_dot(disk->pos, disk->normal);
}
void	cone_disk(t_cone *cone)
{
	t_object	*disk;

	disk = malloc(sizeof(t_object));
	if (!disk)
		ft_error(ENOMEM);
	disk->disk.type = disk_obj;
	disk->disk.pos = cone->pos;
	disk->disk.radius = cone->radius;
	disk->disk.colour = cone->colour;
	disk->disk.normal = cone->normal;
	cone->bottom = disk;
}

void	create_cone(t_cone *cone, char *line)
{
	cone->type = cone_obj;
	line += 3;
	cone->pos = get_vec3(&line);
	cone->normal = get_vec3(&line);
	cone->disk_hit = 0;
	vec3_normalize(&cone->normal);
	ft_skip_ws(&line);
	cone->radius = get_float(&line, REAL) / 2;
	ft_skip_ws(&line);
	cone->height = get_float(&line, REAL);
	ft_skip_ws(&line);
	cone->colour = get_colour(&line);
	cone_disk(cone); // TODO: free this
	t_vec3 tip_to_base = vec3_multf(cone->normal, cone->height);
	cone->center = vec3_add(cone->pos, vec3_multf(tip_to_base, 0.5f));
	print_vec3(cone->center, "cone center");
	cone->angle = (cone->radius / cone->height) * (cone->radius / cone->height);
}
