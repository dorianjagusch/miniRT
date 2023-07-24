/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:29 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/24 09:57:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minirt.h"
#include	"objects.h"
#include	"libft.h"
#include	"scene.h"

t_vec3	get_vec3_mesh(char *line)
{
	t_vec3	vec;

	ft_skip_ws(&line);
	vec.x = ft_atof(line);
	ft_skip_num(&line, REAL);
	ft_skip_ws(&line);
	vec.y = ft_atof(line);
	ft_skip_num(&line, REAL);
	ft_skip_ws(&line);
	vec.z = ft_atof(line);
	if (*line == '-')
		line += 1;
	ft_skip_num(&line, REAL);
	return (vec);
}

void	get_faces(char *line, t_vec3_face	*key, t_mesh *mesh)
{
	char	**split ;
	int		i;

	i = 0;
	split = ft_split3(line, '/', ' ');
	while (i < 3)
	{
		if (mesh->count_vt != 0)
		{
			key[i].v = ft_atoi(split[i * 3]);
			key[i].t = ft_atoi(split[i * 3 + 1]);
			key[i].n = ft_atoi(split[i * 3 + 2]);
		}
		else
		{
			key[i].v = ft_atoi(split[i * 2]);
			key[i].t = 0;
			key[i].n = ft_atoi(split[i * 2 + 1]);
		}
		i++;
	}
	ft_free_anyarray((void *) &split, 6);
}

static void	count_file_objects(int fd, char *file_name, t_mesh *mesh)
{
	char	*line;

	line = get_next_line(fd, FALSE);
	while (line)
	{
		if (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ')
			mesh->count_v++;
		else if (!ft_empty_str(line) && !ft_strncmp("vn", line, 2) \
		&& line[2] == ' ')
			mesh->count_vn++;
		else if (!ft_empty_str(line) && !ft_strncmp("vt", line, 1) \
		&& line[2] == ' ')
			mesh->count_vt++;
		else if (!ft_empty_str(line) && !ft_strncmp("f", line, 1) \
		&& line[1] == ' ')
			mesh->count_f++;
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	if (line)
		free(line);
	if (close(fd) < 0)
		ft_error(errno);
}

t_vec2	get_textures(char *line)
{
	t_vec2	vec;

	ft_skip_ws(&line);
	vec.x = ft_atof(line);
	ft_skip_num(&line, REAL);
	ft_skip_ws(&line);
	vec.y = ft_atof(line);
	ft_skip_num(&line, REAL);
	ft_skip_ws(&line);
	if (*line == '-')
		line += 1;
	ft_skip_num(&line, REAL);
	return (vec);
}

static void	init_arrays(t_mesh *mesh, int fd)
{
	char	*line;
	int		count;

	line = get_next_line(fd, FALSE);
	count = 0;
	while (line)
	{
		while (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ')
		{
			mesh->vertex[count] = get_vec3_mesh(line + 1);
			count++;
			if (line)
				free(line);
			line = get_next_line(fd, FALSE);
		}
		count = 0;
		while (!ft_empty_str(line) && !ft_strncmp("vn", line, 2) && line[2] == ' ' && line)
		{
			mesh->normals[count] = get_vec3_mesh(line + 2);
			count++;
			if (line)
				free(line);
			line = get_next_line(fd, FALSE);
		}
		count = 0;
		while (!ft_empty_str(line) && !ft_strncmp("vt", line, 2) && line[2] == ' ' && line && mesh->count_vt != 0)
		{
			mesh->textures[count] = get_textures(line + 2);
			count++;
			if (line)
				free(line);
			line = get_next_line(fd, FALSE);
		}
		count = 0;
		while (!ft_empty_str(line) && !ft_strncmp("f", line, 1) && line[1] == ' ' && line)
		{
			get_faces(line + 1, mesh->faces[count], mesh);
			count++;
			if (line)
				free(line);
			line = get_next_line(fd, FALSE);
		}
		if (line)
			free(line);
		line = get_next_line(fd, FALSE);
	}
	if (line)
		free(line);
	if (close(fd) < 0)
		ft_error(errno);
}

void free_arrays(t_mesh *mesh)
{
	int	count;

	if (mesh->normals)
		free(mesh->normals);
	if (mesh->vertex)
		free(mesh->vertex);
	if (mesh->textures)
		free(mesh->textures);
	if (mesh->faces)
	{
		count = 0;
		while (count < mesh->count_f)
		{
			free(mesh->faces[count]);
			count++;
		}
	}
}

void	create_mesh(t_mesh *mesh)
{
	int	index;

	index = 0;
	mesh->n_triangles = mesh->count_f;
	mesh->triangle_data = malloc(mesh->n_triangles * sizeof(t_object));
	while (index < mesh->n_triangles)
	{
		mesh->triangle_data[index].type = triangle_obj;
		mesh->triangle_data[index].triangle.normal = \
		mesh->normals[(mesh->faces[index]->n) - 1];
		mesh->triangle_data[index].triangle.tri_point[0] = \
		mesh->vertex[(mesh->faces[index][0].v) - 1];
		mesh->triangle_data[index].triangle.tri_point[1] = \
		mesh->vertex[(mesh->faces[index][1].v) - 1];
		mesh->triangle_data[index].triangle.tri_point[2] = \
		mesh->vertex[(mesh->faces[index][2].v) - 1];
		mesh->triangle_data[index].triangle.colour = (t_vec4) {1, 1, 0, 1};
		mesh->triangle_data[index].triangle.edges[0] = 
		vec3_sub(mesh->triangle_data[index].triangle.tri_point[1],
			mesh->triangle_data[index].triangle.tri_point[0]);
		mesh->triangle_data[index].triangle.edges[1] = 
		vec3_sub(mesh->triangle_data[index].triangle.tri_point[2],\
			mesh->triangle_data[index].triangle.tri_point[0]);
		index++;
	}
}

void ascii_parser(t_mesh *mesh, char *line)
{
	int		fd;
	char	*file_name;
	int		count;
	int		index;

	line += 3;
	mesh->type = mesh_obj;
	mesh->obj_id = -1;
	file_name = *ft_split2(line);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	count_file_objects(fd, file_name, mesh);
	mesh->vertex = malloc(mesh->count_v * sizeof(t_vec3));
	mesh->normals = malloc(mesh->count_vn * sizeof(t_vec3));
	if (mesh->count_vt != 0)
		mesh->textures = malloc(mesh->count_vt * sizeof(t_vec2));
	mesh->faces = malloc(mesh->count_f * sizeof(t_vec3_face *));
	count = 0;
	while (count < mesh->count_f)
	{
		mesh->faces[count] = malloc(3 * sizeof(t_vec3_face));
		count++;
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	init_arrays(mesh, fd);
	index = 0;
	while (index < mesh->count_vn)
		index++;
	close(fd);
	create_mesh(mesh);
	free_arrays(mesh);
	free(file_name);
}