/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 17:09:43 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "shaders_bonus.h"
#include "scene_bonus.h"

static void	set_object(t_img *img, char *line, int id)
{
	if (!ft_isspace(line[2]))
		ft_error(ident_err);
	if (!ft_strncmp("sp", line, 2))
		create_sphere(&img->scene->objs[id].sphere, line);
	else if (!ft_strncmp("tm", line, 2))
		ascii_parser(&img->scene->objs[id].mesh, line);
	else if (!ft_strncmp("pl", line, 2))
		create_plane(&img->scene->objs[id].plane, line);
	else if (!ft_strncmp("cy", line, 2))
		create_cylinder(&img->scene->objs[id].cylinder, line);
	else if (!ft_strncmp("di", line, 2))
		create_disk(&img->scene->objs[id].disk, line);
	else if (!ft_strncmp("tr", line, 2))
		create_triangle(&img->scene->objs[id].triangle, line);
	else if (!ft_strncmp("co", line, 2))
		create_cone(&img->scene->objs[id].cone, line);
	else
		ft_error(ident_err);
	set_picture(img, &img->scene->objs[id].meta.tex_col,
		&img->scene->objs[id].meta.colour, line);
	set_normals(img, &img->scene->objs[id].meta.tex_norm, line);
}

static void	process_line(t_img *img, char *line)
{
	static int	id;

	if (line && line[0] != '\n')
	{
		ft_skip_ws(&line);
		if (line && ft_isupper(*line))
			set_unique(img->scene, &line);
		else if (line)
		{
			set_object(img, line, id);
			// check_visibility(img->scene, id);
			id++;
		}
	}
}

static int	count_objects(int fd, char *av)
{
	char	*line;
	int		count;

	line = get_next_line(fd, FALSE);
	count = 0;
	while (line)
	{
		if (!ft_empty_str(line) && is_obj(line))
			count++;
		free(line);
		line = get_next_line(fd , FALSE);
	}
	if (close(fd) < 0)
		ft_error(errno);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	return (count);
}

void	set_scene(t_img *img, t_scene *scene, char *av)
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
	line = get_next_line(fd, FALSE);
	while (line != NULL)
	{
		if (!ft_empty_str(line) && ft_strncmp(line, "#", 1))
			process_line(img, line);
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	close(fd);
}
