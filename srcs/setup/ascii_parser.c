#include "minirt.h"
# include "objects.h"
# include "libft.h"
# include "scene.h"

t_vec3	get_vec3_mesh(char **line)
{
	t_vec3	vec;

	DEBUG_ONLY(printf("line at start of vec3 = |%s|\n", *line));
	ft_skip_ws(line);
	DEBUG_ONLY(printf("line befor vec3.x = |%s|\n", *line));
	vec.x = ft_atof(*line);
	ft_skip_num(line, REAL);
	DEBUG_ONLY(printf("line vec.x = |%s|\n", *line));
	ft_skip_ws(line);
	vec.y = ft_atof(*line);
	DEBUG_ONLY(printf("line vec.y = |%s|\n", *line));
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	vec.z = ft_atof(*line);
	DEBUG_ONLY(printf("line vec.z = |%s|\n", *line));
	if (**line == '-')
		*line += 1;
	ft_skip_num(line, REAL);
	return (vec);
}

static void	count_file_objects(int fd, char *file_name, t_mesh *mesh) //TODO: this is not great....
{ //v, vn, vt, f 
	char	*line;

	mesh->count_v = 0;
	mesh->count_vn = 0;
	mesh->count_vt = 0;
	mesh->count_f = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ') //TODO: no this should handle WS in a not shit way
			mesh->count_v++;
		else if (!ft_empty_str(line) && !ft_strncmp("vn", line, 2) && line[2] == ' ') //TODO: no this should handle WS in a not shit way
			mesh->count_vn++;
		else if (!ft_empty_str(line) && !ft_strncmp("vt", line, 1) && line[2] == ' ') //TODO: no this should handle WS in a not shit way
			mesh->count_vt++;
		else if (!ft_empty_str(line) && !ft_strncmp("f", line, 1) && line[1] == ' ') //TODO: no this should handle WS in a not shit way
			mesh->count_f++;
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	DEBUG_ONLY(printf("V: %f	VN: %f	VT: %f	F: %f\n\n", mesh->count_v ,mesh->count_vn, mesh->count_vt, mesh->count_f));
	if (close(fd) < 0)
		ft_error(errno);
}

static void init_arrays(t_mesh *mesh, int fd)
{
	char *line;
	int count;

	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		while (!ft_empty_str(line) && !ft_strncmp("v", line, 1) && line[1] == ' ' && line) //TODO: no this should handle WS in a not shit way
		{
			line += 1;
			mesh->vertex[count] = get_vec3_mesh(&line);
			count++;
			DEBUG_ONLY(print_vec3(mesh->vertex[count], "vertex"));
			line = get_next_line(fd);
		}
		// count = 0;
		// while (!ft_empty_str(line) && !ft_strncmp("vn", line, 2) && line[2] == ' ' && line) //TODO: no this should handle WS in a not shit way
		// {
		// 	line += 2;
		// 	mesh->normals[count] = get_vec3_mesh(&line);
		// 	count++;
		// 	DEBUG_ONLY(print_vec3(mesh->normals[count], "normals"));
		// 	line = get_next_line(fd);
		// }
		// count = 0;
		// while (!ft_empty_str(line) && !ft_strncmp("vt", line, 2) && line[2] == ' ' && line) //TODO: no this should handle WS in a not shit way
		// {
		// 	// line += 2;
		// 	// // mesh->textures[count] = get_vec2_mesh(&line);// need to write this
		// 	// count++;
		// 	// //DEBUG_ONLY(print_vec2(mesh->normals[count], "textures"));
		// 	line = get_next_line(fd);
		// }
		// count = 0;
		// while (!ft_empty_str(line) && !ft_strncmp("f", line, 1) && line[1] == ' ' && line) //TODO: no this should handle WS in a not shit way
		// {
		// 	line += 1;
		// 	mesh->faces[count] = get_vec3_mesh(&line);
		// 	count++;
		// 	DEBUG_ONLY(print_vec3(mesh->normals[count], "faces"));
		// 	line = get_next_line(fd);
		// }
		free(line);
		line = get_next_line(fd);
	}
	
	if (close(fd) < 0)
		ft_error(errno);

}

// void	create_mesh(t_mesh *mesh, int fd)
// {
// }

void ascii_parser(t_mesh *mesh, char *line)
{
    int             fd;
    unsigned int    number_triangles;
	char			*file_name;

	line += 3;
	mesh->type = mesh_obj;
	file_name = *ft_split2(line);
    fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	count_file_objects(fd, file_name, mesh);
	//TODO: create an array of vec3 or objects, parse the information in including normals, colour and material
	//render the frigging object, WHY IS THIS SO FRIGGING HARD
    mesh->vertex = malloc(mesh->count_v * sizeof(t_vec3)); 
	mesh->normals = malloc(mesh->count_vn * sizeof(t_vec3));
    mesh->textures = malloc(mesh->count_vt * sizeof(t_vec2));
    mesh->faces = malloc(mesh->count_f * sizeof(t_vec3));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	//PARSE THEM HERE
	init_arrays(mesh, fd);
	exit (0);//
	//create_mesh(mesh, fd);
	free(file_name);
	free(line);
    close(fd);
	exit(0); //
}

//TODO: vertex array,array of the normals, array of the textures THEN each triangle is intialized with the matchin pooints for point A, B and C plus matching texture etc
