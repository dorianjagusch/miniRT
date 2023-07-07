/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 15:53:05 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void set_unique(t_scene *scene, char **line)
{
	static int flag[3];

	if (ft_strncmp("A ", *line, 2) == 0 && !flag[0])
	{
		*line += 2;									// needs to be 2 to skip the A and white space
		scene->amb.ratio = get_float(line, RATIO); // this needs to be changed to intensity
		scene->amb.colour = get_colour(line);
		flag[0] = 1;
		scene->amb.valid = 1;
	}
	else if (ft_strncmp("L ", *line, 2) == 0 && !flag[1])
	{
		*line += 2;
		scene->light.pos = get_vec3(line);
		ft_skip_ws(line);
		scene->light.ratio = get_float(line, RATIO);
		scene->light.colour = get_colour(line);
		flag[1] = 1;
		scene->light.valid = 1;
	}
	else if (ft_strncmp("C ", *line, 2) == 0 && !flag[2])
	{
		*line += 2;
		scene->cam.pos = get_vec3(line);
		scene->cam.dir = get_vec3(line);
		scene->cam.fov = get_float(line, ANGLE);
		scene->cam.aspect_ratio = (float)WIDTH / (float)HEIGHT;
		vec3_normalize(&scene->cam.dir);
		flag[2] = 1;
		scene->cam.valid = 1;
	}
	else
		ft_error(ident_err);
}

static void	set_object(t_scene *scene, char *line, int id)
{
	if (!ft_isspace(line[2]))
		ft_error(ident_err);
	if (!ft_strncmp("sp", line, 2))
		create_sphere(&scene->objs[id].sphere, line);
	else if (!ft_strncmp("tm", line, 2))
		binary_parser(&scene->objs[id].mesh, line);
	else if (!ft_strncmp("pl", line, 2))
		create_plane(&scene->objs[id].plane, line);
	else if (!ft_strncmp("cy", line, 2))
		create_cylinder(&scene->objs[id].cylinder, line);
	else if (!ft_strncmp("di", line, 2))
		create_disk(&scene->objs[id].disk, line);
	else if (!ft_strncmp("tr", line, 2))
		create_triangle(&scene->objs[id].triangle, line);
	else if (!ft_strncmp("bo", line, 2))
		create_box(&scene->objs[id].box, line);
	else
		ft_error(ident_err);
}

static void	process_line(t_scene *scene, char *line)
{
	static int	id;

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

static int	count_objects(int fd, char *av)
{
	char	*line;
	int		count;

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

void	set_scene(t_scene *scene, char *av)
{
	int		fd;
	char	*line;

	if (ft_strncmp(av + strlen(av) - EXT_LEN, EXTENSION, EXT_LEN))
		ft_error(file_err);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	scene->n_objs = count_objects(fd, av);
	if (scene->n_objs < 0)
		ft_error(content_err);
	scene->objs = ft_calloc(scene->n_objs, sizeof(t_object));
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
