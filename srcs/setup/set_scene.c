/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/26 17:19:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_unique(t_scene *scene, char **line)
{
	static int	flag[3];

	if (ft_strncmp("A ", *line, 2) == 0 && !flag[0])
	{
		*line += 2; // needs to be 2 to skip the A and white space
		scene->amb.ratio = get_double(line, RATIO);
		scene->amb.colour = get_colour(line);
		flag[0] = 1;
		scene->amb.valid = 1;
		//ft_printf("filled ambient\n");
	}
	else if (ft_strncmp("L ", *line, 2) == 0 && !flag[1])
	{
		*line += 2; // needs to be 2 to skip the L and white space
		scene->light.pos = get_vec3(line);
		ft_skip_ws(line);
		scene->light.ratio = get_double(line, RATIO);
		scene->light.colour = get_colour(line);
		flag[1] = 1;
		scene->light.valid = 1;
		// printf("light ratio = %f\n", scene->light.ratio);
		// printf("_____________________\n");
		// ft_printf("filled light\n");
	}
	else if (ft_strncmp("C ", *line, 2) == 0 && !flag[2])
	{
		*line += 2;
		scene->cam.pos = get_vec3(line);
		scene->cam.forward = get_vec3(line);
		scene->cam.fov = get_double(line, ANGLE);
		init_camera_dir(&scene->cam);
		flag[2] = 1;
		scene->cam.valid = 1;
		// printf("_____________________\n");
		// printf("\n\ncam.pos.x: %f, cam.pos.y: %f, cam.pos.z: %f\n", scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
		// printf("\n\ncam.forward.x: %f, cam.forward.y: %f, cam.forward.z: %f\n", scene->cam.forward.x, scene->cam.forward.y, scene->cam.forward.z);
		// printf("\n\ncam.fov: %f\n", scene->cam.fov);
		// printf("_____________________\n");
		// ft_printf("filled camera\n");
	}
	else
		ft_error(ident_err);
}

static void	get_object(t_scene *scene, char *line, t_obj *offset)
{
	if (!ft_strncmp("sp ", line, 3))
		offset->type = sphere;
	else if (!ft_strncmp("pl ", line, 3))
		offset->type = plane;
	else if (!ft_strncmp("cy ", line, 3))
		offset->type = cylinder;
	else
		ft_error(ident_err);
	line += 3;
	offset->position = get_vec3(&line);
	if (offset->type != sphere)
		offset->normal = get_vec3(&line);
	ft_skip_ws(&line);
	if (offset->type != plane)
		offset->radius = get_double(&line, REAL) / 2;
	if (offset->type == cylinder)
		offset->height = get_double(&line, REAL);
	//offset->material = get_int(&line);
	//offset->normal = get_int(&line);
	ft_skip_ws(&line);
	offset->colour = get_colour(&line);
}

static void	process_line(t_scene *scene, char *line)
{
	static t_obj	*offset;
	int				i = 0;

	offset = scene->objs;
	if (line && line[0] != '\n')
	{
		ft_skip_ws(&line);
		if (line && ft_isupper(*line))
			get_unique(scene, &line);
		else if (line)
		{
			get_object(scene, line, offset); // also what does the offset thing mean? //just a pointer to keep track of the object
			offset++;
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
	ft_printf("There are %d objects\n", scene->n_objs);
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
