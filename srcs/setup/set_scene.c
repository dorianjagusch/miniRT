/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 16:56:26 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void set_unique(t_scene *scene, char **line)
{
	static int flag[3];

	if (ft_strncmp("A ", *line, 2) == 0 && !flag[0])
	{
		*line += 2;									// needs to be 2 to skip the A and white space
		scene->amb.ratio = get_double(line, RATIO); // this needs to be changed to intensity
		scene->amb.colour = get_colour(line);
		flag[0] = 1;
		scene->amb.valid = 1;
	}
	else if (ft_strncmp("L ", *line, 2) == 0 && !flag[1])
	{
		*line += 2;
		scene->light.pos = get_vec3(line);
		ft_skip_ws(line);
		scene->light.ratio = get_double(line, RATIO);
		scene->light.colour = get_colour(line);
		flag[1] = 1;
		scene->light.valid = 1;
	}
	else if (ft_strncmp("C ", *line, 2) == 0 && !flag[2])
	{
		*line += 2;
		scene->cam.pos = get_vec3(line);
		scene->cam.dir = get_vec3(line);
		scene->cam.fov = get_double(line, ANGLE);
		scene->cam.aspect_ratio = (double)WIDTH / (double)HEIGHT;
		vec3_normalize(&scene->cam.dir);
		flag[2] = 1;
		scene->cam.valid = 1;
	}
	else
		ft_error(ident_err);
}

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

static void set_object(t_scene *scene, char *line, int id)
{
	if (!ft_strncmp("sp ", line, 3))
	{
		scene->objs[id].type = sphere;
		create_sphere(&scene->objs[id], line);
	}
	else if (!ft_strncmp("pl ", line, 3))
	{
		scene->objs[id].type = plane;
		create_plane(&scene->objs[id], line);
	}
	else if (!ft_strncmp("cy ", line, 3))
	{
		scene->objs[id].type = cylinder;
		create_cylinder(&scene->objs[id], line);
	}
	else if (!ft_strncmp("di ", line, 3))
	{
		scene->objs[id].type = disk;
		create_disk(&scene->objs[id], line);
	}
	else
		ft_error(ident_err);
}

static void process_line(t_scene *scene, char *line)
{
	static int id;

	if (line && line[0] != '\n')
	{
		ft_skip_ws(&line);
		if (line && ft_isupper(*line))
			set_unique(scene, &line);
		else if (line)
		{
			set_object(scene, line, id);
			id++;
		}
	}
}

static int count_objects(int fd, char *av)
{
	char *line;
	int count;

	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		if (!ft_empty_str(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		ft_error(errno);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	return (count - 3);
}

void set_scene(t_scene *scene, char *av)
{
	int fd;
	char *line;

	if (ft_strncmp(av + strlen(av) - EXT_LEN, EXTENSION, EXT_LEN))
		ft_error(file_err);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	scene->n_objs = count_objects(fd, av);
	if (scene->n_objs < 0)
		ft_error(content_err);
	scene->objs = ft_calloc(scene->n_objs, sizeof(t_obj));
	if (!scene->objs)
		ft_error(ENOMEM);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!ft_empty_str(line))
			process_line(scene, line);
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
