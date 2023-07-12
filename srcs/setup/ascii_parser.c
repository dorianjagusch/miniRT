/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:29 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/12 09:08:49 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# include "objects.h"
# include "libft.h"
# include "scene.h"

t_vec3	get_vec3_mesh(char **line)
{
	t_vec3	vec;

	ft_skip_ws(line);
	vec.x = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	vec.y = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	vec.z = ft_atof(*line);
	if (**line == '-')
		*line += 1;
	ft_skip_num(line, REAL);
	return (vec);
}

void get_faces(char **line, t_vec3_face	*key)
{
	char **split = ft_split3(*line, '/', ' ');
	int i;
	
	i = 0;
	
	while (i < 3)
	{
		key[i].v = ft_atoi(split[i * 3]);
		key[i].t = ft_atoi(split[i * 3 + 1]);
		key[i].n = ft_atoi(split[i * 3 + 2]);
		i++;
	}
	free(split);
}

static void	count_file_objects(int fd, char *file_name, t_mesh *mesh)
{
	char	*line;

	mesh->count_v = 0;
	mesh->count_vn = 0;
	mesh->count_vt = 0;
	mesh->count_f = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ')
			mesh->count_v++;
		else if (!ft_empty_str(line) && !ft_strncmp("vn", line, 2) && line[2] == ' ')
			mesh->count_vn++;
		else if (!ft_empty_str(line) && !ft_strncmp("vt", line, 1) && line[2] == ' ')
			mesh->count_vt++;
		else if (!ft_empty_str(line) && !ft_strncmp("f", line, 1) && line[1] == ' ')
			mesh->count_f++;
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	DEBUG_ONLY(printf("V: %f	VN: %f	VT: %f	F: %f\n\n", mesh->count_v ,mesh->count_vn, mesh->count_vt, mesh->count_f));
	if (close(fd) < 0)
		ft_error(errno);
}

t_vec2 get_textures(char **line)
{
	t_vec2	vec;

	ft_skip_ws(line);
	vec.x = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	vec.y = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	if (**line == '-')
		*line += 1;
	ft_skip_num(line, REAL);
	return (vec);
}

static void init_arrays(t_mesh *mesh, int fd)
{
	char *line;
	int count;

	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		while (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ' && line)
		{
			line += 1;
			mesh->vertex[count] = get_vec3_mesh(&line);
			DEBUG_ONLY(print_vec3(mesh->vertex[count], "vertex"));
			count++;
			line = get_next_line(fd);
		}
		count = 0;
		while (!ft_empty_str(line) && !ft_strncmp("vn", line, 2) && line[2] == ' ' && line)
		{
			line += 2;
			mesh->normals[count] = get_vec3_mesh(&line);
			DEBUG_ONLY(print_vec3(mesh->normals[count], "normals"));
			count++;
			line = get_next_line(fd);
		}
		count = 0;
		while (!ft_empty_str(line) && !ft_strncmp("vt", line, 2) && line[2] == ' ' && line)
		{
			line += 2;
			mesh->textures[count] = get_textures(&line);
			DEBUG_ONLY(printf("vec.x: %f	vec.y: %f\n", mesh->textures[count].x, mesh->textures[count].y));
			count++;
			line = get_next_line(fd);
		}
		count = 0;
		while (!ft_empty_str(line) && !ft_strncmp("f", line, 1) && line[1] == ' ' && line)
		{
			line += 1;
			get_faces(&line, mesh->faces[count]);
			DEBUG_ONLY(printf("vertex: %d	texture: %d		normal: %d\n", mesh->faces[count][0].v, mesh->faces[count][0].t, mesh->faces[count][0].n));
			DEBUG_ONLY(printf("vertex: %d	texture: %d		normal: %d\n", mesh->faces[count][1].v, mesh->faces[count][1].t, mesh->faces[count][1].n));
			DEBUG_ONLY(printf("vertex: %d	texture: %d		normal: %d\n", mesh->faces[count][2].v, mesh->faces[count][2].t, mesh->faces[count][2].n));
			count++;
			line = get_next_line(fd);
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		ft_error(errno);

}

// typedef struct s_triangle
// {
// 	t_obj_e			type;
// 	t_vec3			tri_point[3];
// 	t_vec3			normal;
// 	t_vec3			edges[2];
// 	t_vec4			colour;
// 	t_material_e	material;
// }					t_triangle;

// typedef struct s_mesh
// {
// 	t_obj_e			type;
// 	float			n_triangles;
// 	float			count_v;
// 	float			count_vn;
// 	float			count_vt;
// 	float			count_f;
// 	t_vec3			*vertex;
// 	t_vec3			*normals;
// 	t_vec2			*textures;
// 	t_vec3_face		**faces;
// 	t_vec4			colour;
// 	int				obj_id;//
// 	t_material_e	material;//
// 	t_object		*triangle_data; //
// }					t_mesh;

void	create_mesh(t_mesh *mesh)
{
	int index;

	index = 0;
	mesh->n_triangles = mesh->count_f;
	mesh->triangle_data = malloc(mesh->n_triangles * sizeof(t_object));
		printf("mesh->faces[index]->v = %d\n", mesh->faces[index]->v);
	while (index < mesh->n_triangles)
	{
		mesh->triangle_data[index].type = triangle_obj;
		mesh->triangle_data[index].triangle.normal = mesh->normals[mesh->faces[index]->n];
		mesh->triangle_data[index].triangle.tri_point[0] = mesh->vertex[(mesh->faces[index][0].v) - 1];
		print_vec3(mesh->triangle_data[index].triangle.tri_point[0], "tripoint 0");
		mesh->triangle_data[index].triangle.tri_point[1] = mesh->vertex[(mesh->faces[index][1].v) - 1];
		print_vec3(mesh->triangle_data[index].triangle.tri_point[1], "tripoint 1");
		mesh->triangle_data[index].triangle.tri_point[2] = mesh->vertex[(mesh->faces[index][2].v) - 1];
		print_vec3(mesh->triangle_data[index].triangle.tri_point[2], "tripoint 2");
		mesh->triangle_data[index].triangle.colour = (t_vec4) {1, 1, 0, 1};
		mesh->triangle_data[index].triangle.edges[0] = vec3_sub(mesh->triangle_data[index].triangle.tri_point[1], mesh->triangle_data[index].triangle.tri_point[0]);
		mesh->triangle_data[index].triangle.edges[1] = vec3_sub(mesh->triangle_data[index].triangle.tri_point[2], mesh->triangle_data[index].triangle.tri_point[0]);

		index++;
	}
}


void ascii_parser(t_mesh *mesh, char *line)
{
	int             fd;
	char			*file_name;
	int				count;

	line += 3;
	mesh->type = mesh_obj;
	mesh->obj_id = -1;
	file_name = *ft_split2(line);
	DEBUG_ONLY(printf("%s", file_name));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	count_file_objects(fd, file_name, mesh);
	mesh->vertex = malloc(mesh->count_v * sizeof(t_vec3)); 
	mesh->normals = malloc(mesh->count_vn * sizeof(t_vec3));
	mesh->textures = malloc(mesh->count_vt * sizeof(t_vec2));
	mesh->faces = malloc(mesh->count_f * sizeof(t_vec3_face*));
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
	close(fd);
	create_mesh(mesh);
	// free(file_name);
	// free(line);

}

//TODO: vertex array,array of the normals, array of the textures THEN each triangle is intialized with the matchin pooints for point A, B and C plus matching texture etc
