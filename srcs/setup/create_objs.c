#include "minirt.h"

void create_sphere(t_obj *obj, char *line)
{
	line += 3;
	obj->pos = get_vec3(&line);
	ft_skip_ws(&line);
	obj->radius = get_double(&line, REAL) / 2;
	obj->radius2 = pow(obj->radius, 2.0);
	ft_skip_ws(&line);
	obj->colour = get_colour(&line);
}

void create_cylinder(t_obj *obj, char *line)
{
	line += 3;
	obj->pos = get_vec3(&line);
	obj->normal = get_vec3(&line);
	vec3_normalize(&obj->normal);
	ft_skip_ws(&line);
	obj->radius = get_double(&line, REAL) / 2;
	obj->radius2 = pow(obj->radius, 2.0);
	ft_skip_ws(&line);
	obj->height = get_double(&line, REAL);
	ft_skip_ws(&line);
	obj->colour = get_colour(&line);
}

void create_plane(t_obj *obj, char *line)
{
	line += 3;
	obj->pos = get_vec3(&line);
	ft_skip_ws(&line);
	obj->normal = get_vec3(&line);
	vec3_normalize(&obj->normal);
	ft_skip_ws(&line);
	obj->colour = get_colour(&line);
	obj->d = -vec3_dot(obj->pos, obj->normal);
}

void create_disk(t_obj *obj, char *line)
{
	line += 3;
	obj->pos = get_vec3(&line);
	ft_skip_ws(&line);
	obj->normal = get_vec3(&line);
	vec3_normalize(&obj->normal);
	ft_skip_ws(&line);
	obj->radius = get_double(&line, REAL) / 2;
	ft_skip_ws(&line);
	obj->colour = get_colour(&line);
	obj->d = -vec3_dot(obj->pos, obj->normal);
}