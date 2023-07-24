/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene_man.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 09:51:32 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_object(t_scene *scene, char *line, int id)
{
	if (!ft_isspace(line[2]))
		ft_error(ident_err);
	if (!ft_strncmp("sp", line, 2))
		create_sphere(&scene->objs[id].sphere, line);
	else if (!ft_strncmp("pl", line, 2))
		create_plane(&scene->objs[id].plane, line);
	else if (!ft_strncmp("cy", line, 2))
		create_cylinder(&scene->objs[id].cylinder, line);
	else if (!ft_strncmp("di", line, 2))
		create_disk(&scene->objs[id].disk, line);
	else
		ft_error(ident_err);
	set_meta(&scene->objs[id]); //TODO: is this needed?
	check_visibility(scene, id);
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
		if (!ft_empty_str(line) && is_obj(line))
			count++;
		free(line);
		line = get_next_line(fd);
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
	scene->lights = ft_calloc(sizeof(t_light) * 7, 1);
	scene->n_lights = 0;
	if (!scene->objs)
		ft_error(ENOMEM);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!ft_empty_str(line) && ft_strncmp(line, "#", 1))
			process_line(scene, line);
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
