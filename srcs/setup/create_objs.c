#include "minirt.h"

void	create_sphere(t_sphere *sphere, char *line)
{
	sphere->type = sphere_obj;
	line += 3;
	sphere->pos = get_vec3(&line);
	ft_skip_ws(&line);
	sphere->radius = get_double(&line, REAL) / 2;
	sphere->radius2 = pow(sphere->radius, 2.0);
	ft_skip_ws(&line);
	sphere->colour = get_colour(&line);
}

void	create_cylinder(t_cylinder *cylinder, char *line)
{
	cylinder->type = cylinder_obj;
	line += 3;
	cylinder->pos = get_vec3(&line);
	cylinder->normal = get_vec3(&line);
	vec3_normalize(&cylinder->normal);
	ft_skip_ws(&line);
	cylinder->radius = get_double(&line, REAL) / 2;
	cylinder->radius2 = pow(cylinder->radius, 2.0);
	ft_skip_ws(&line);
	cylinder->height = get_double(&line, REAL);
	ft_skip_ws(&line);
	cylinder->colour = get_colour(&line);
}

void	create_plane(t_plane *plane, char *line)
{
	plane->type = plane_obj;
	line += 3;
	plane->pos = get_vec3(&line);
	ft_skip_ws(&line);
	plane->normal = get_vec3(&line);
	vec3_normalize(&plane->normal);
	ft_skip_ws(&line);
	plane->colour = get_colour(&line);
	plane->d = -vec3_dot(plane->pos, plane->normal);
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
	disk->radius = get_double(&line, REAL) / 2;
	ft_skip_ws(&line);
	disk->colour = get_colour(&line);
	disk->d = -vec3_dot(disk->pos, disk->normal);
}

void	create_triangle(t_triangle *triangle, char *line)
{
	triangle->type = triangle_obj;
	DEBUG_ONLY(printf("in the create triangle function\n"));
	line += 3;
	triangle->verts[0] = get_vec3(&line);
	DEBUG_ONLY(print_vec3(triangle->pos, "triangle :"));
	ft_skip_ws(&line);
	triangle->verts[1] = get_vec3(&line);
	ft_skip_ws(&line);
	triangle->verts[2] = get_vec3(&line);
	ft_skip_ws(&line);
	// triangle->normal = get_vec3(&line);
	// vec3_normalize(&triangle->normal);
	ft_skip_ws(&line);
	triangle->colour = get_colour(&line);
	DEBUG_ONLY(print_vec4(triangle->colour, "triangle :"));
	triangle->edges[0] = vec3_sub(triangle->verts[0], triangle->verts[1]);
	triangle->edges[0] = vec3_sub(triangle->verts[0], triangle->verts[2]);
}
