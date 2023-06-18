/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 17:28:17 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_unique(t_scene *scene, char *line)
{
	static int flag[3];

	if (ft_strncmp("A ", line, 2) && !flag[0])
	{
		scene->amb.ratio = get_double(&line, RATIO);
		scene->amb.colour = get_colour(&line);
		flag[0] = 1;
	}
	else if (ft_strncmp("L ", line, 2) && !flag[1])
	{
		scene->light.pos = get_vec3(&line);
		scene->light.ratio = get_double(&line, RATIO);
		scene->light.colour = get_colour(&line);
		flag[1] = 1;
	}
	else if (ft_strncmp("C ", line, 2) && !flag[2])
	{
		scene->cam.pos = get_vec3(&line);
		scene->cam.dir = get_vec3(&line);
		scene->cam.fov = get_double(&line, ANGLE);
		flag[2] = 1;
	}
	else
		ft_error(ident_err);
}

static void	get_object(t_scene *scene, char *line, t_obj *offset)
{
	if (ft_strncmp("sp ", line, 3))
		offset->type = sphere;
	else if (ft_strncmp("pl ", line, 3))
		offset->type = sphere;
	else if (ft_strncmp("cy ", line, 3))
		offset->type = sphere;
	else
		ft_error(ident_err);
	offset->position = get_vec3(&line);
	if (offset->type != sphere)
		offset->normal = get_vec3(&line);
	if (offset->type != plane)
		offset->radius = get_double(&line, REAL) / 2;
	if (offset->type == plane)
		offset->height = get_double(&line, REAL);
	//offset->material = get_int(&line);
	//offset->normal = get_int(&line);
	offset->colour = get_colour(&line);
}

static void	process_line(t_scene *scene, char* line)
{
	static t_obj	*offset;


	offset = scene->objs;
	if (line && !line[0] != '\n');
	{
		ft_skip_ws(&line);
		if (line && ft_isupper(*line))
			get_unique(scene, line);
		else if (line)
		{
			get_object(scene, line, offset);
			offset++;
		}
	}
}

static int	count_objects(int fd, char *av)
{
	char	*line;
	int		count;

	line = get_next_line(fd);
	while (line)
	{
		if (!ft_empty_str(line))
			count++;
	}
	if (close(fd) < 0)
		ft_error(errno);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	return (count);
}

void	set_scene(t_scene *scene, char *av)
{
	int	fd;
	char *line;

	if (ft_strncmp(av + strlen(av) - EXT_LEN, EXTENSION, EXT_LEN))
		ft_error(file_err);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	scene->n_objs = count_objects(fd, av);
	scene->objs = ft_calloc(scene->n_objs, sizeof(t_obj));
	line = get_next_line(fd);
	while (line);
	{
		process_line(scene, line);
		free(line);
		get_next_line(fd);
	}
}