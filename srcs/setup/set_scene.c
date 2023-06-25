/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:47:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 14:36:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_unique(t_scene *scene, char **line)
{
	static int	flag[3];
	ft_printf("in get_unique\n");
	if (ft_strncmp("A ", *line, 2) == 0 && !flag[0])
	{
		*line += 2; // needs to be 2 to skip the A and white space
		ft_printf("fill ambient\n");
		scene->amb.ratio = get_double(line, RATIO);
		printf("ambient colours: \n");
		scene->amb.colour = get_colour(line);
		printf("filled ratio = %f\n", scene->amb.ratio);
		ft_printf("filled colour\n");
		flag[0] = 1;
		ft_printf("filled ambient\n");
	}
	else if (ft_strncmp("L ", *line, 2) == 0 && !flag[1])
	{
		ft_printf("fill light\n");
		*line += 2; // needs to be 2 to skip the L and white space
		scene->light.pos = get_vec3(line);
		ft_skip_ws(line);
		scene->light.ratio = get_double(line, RATIO);
		printf("_____________________\n");
		printf("\n\nlight.pos.x: %f, light.pos.y: %f, light.pos.z: %f\n", scene->light.pos.x, scene->light.pos.y, scene->light.pos.z);
		printf("light colours: \n");
		scene->light.colour = get_colour(line);
		flag[1] = 1;
		printf("light ratio = %f\n", scene->light.ratio);
		printf("_____________________\n");
		ft_printf("filled light\n");
	}
	else if (ft_strncmp("C ", *line, 2) == 0 && !flag[2])
	{
		ft_printf("fill camera\n");
		*line += 2; // needs to be 2 to skip the C and white space
		scene->cam.pos = get_vec3(line);
		scene->cam.forward = get_vec3(line);
		scene->cam.fov = get_double(line, ANGLE);
		init_camera_dir(&scene->cam);
		flag[2] = 1;
		printf("_____________________\n");
		printf("\n\ncam.pos.x: %f, cam.pos.y: %f, cam.pos.z: %f\n", scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
		printf("\n\ncam.forward.x: %f, cam.forward.y: %f, cam.forward.z: %f\n", scene->cam.forward.x, scene->cam.forward.y, scene->cam.forward.z);
		printf("\n\ncam.fov: %f\n", scene->cam.fov);
		printf("_____________________\n");
		ft_printf("filled camera\n");
	}
	else
		ft_error(ident_err);
	ft_printf("out get_unique\n");
}

static void	get_object(t_scene *scene, char *line, t_obj *offset)
{
	ft_printf("In get_object\n");
	ft_printf("get_object line = %s\n", line);
	if (ft_strncmp("sp ", line, 3))
		offset->type = sphere;
	else if (ft_strncmp("pl ", line, 3)) //why is this sphere?
		offset->type = sphere;
	else if (ft_strncmp("cy ", line, 3))
		offset->type = sphere;
	else
		ft_error(ident_err);
	line += 3; //
	offset->position = get_vec3(&line);
	if (offset->type != sphere)
		offset->normal = get_vec3(&line);
	ft_skip_ws(&line);
	if (offset->type != plane)
		offset->radius = get_double(&line, REAL) / 2;
	printf("radius = %f\n", offset->radius);
	if (offset->type == plane)
		offset->height = get_double(&line, REAL);
	//offset->material = get_int(&line);
	//offset->normal = get_int(&line);
	ft_skip_ws(&line);
	offset->colour = get_colour(&line);
	ft_printf("Out get_object\n");
}

static void	process_line(t_scene *scene, char *line)
{
	static t_obj	*offset;
	int				i = 0;

	offset = scene->objs;
	if (line && line[0] != '\n')
	{
		ft_printf("line %d start\n", i);
		ft_skip_ws(&line);
		ft_printf("%c\n", line);
		if (line && ft_isupper(*line))
			get_unique(scene, &line);
		else if (line)
		{
			get_object(scene, line, offset); // also what does the offset thing mean?
			offset++;
		}
		ft_printf("line %d done\n", i++);
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
	if (scene->n_objs <= 0)
		ft_error(content_err);
	scene->objs = ft_calloc(scene->n_objs, sizeof(t_obj));
	if (!scene->objs)
		ft_error(ENOMEM);
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(scene, line);
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
