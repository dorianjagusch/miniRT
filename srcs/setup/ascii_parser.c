#include "minirt.h"
# include "objects.h"
# include "libft.h"
# include "scene.h"

static int	ascii_count_objects(int fd, char *file_name)
{
	int		count;
	char	*line;

	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		if (!ft_empty_str(line) && !ft_strncmp("facet", line, 5))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		ft_error(errno);
	return (count);
}

void	create_mesh(t_mesh *mesh, int fd)
{
	int		index;
	int		vec;
	char	*line;

	index = 0;
	line = get_next_line(fd);
	while(index < mesh->n_triangles && line != NULL)
	{
		vec = 0;
		while (vec != 3)
		{
			if (!ft_empty_str(line) && ft_strncmp(line, "#", 1))
				line = get_next_line(fd);
			if (ft_strncmp(line, "facet normal", 12))
			{
				line += 12;
				ft_skip_ws(&line);
				mesh->triangle_data[index].triangle.normal = get_vec3(&line);
				ft_skip_ws(&line);
				print_vec3(mesh->triangle_data[index].triangle.normal, "triangle normal");
			}
			if (ft_strncmp(line, "vertex", 6))
			{
				line += 6;
				ft_skip_ws(&line);
				mesh->triangle_data[index].triangle.tri_point[vec] = get_vec3(&line);
				ft_skip_ws(&line);
				print_vec3(mesh->triangle_data[index].triangle.tri_point[0], "triangle normal");
			}
			if (line)
				free(line);
			line = get_next_line(fd);
		}
		// set_triangle_data()
		// mesh->triangle_data[index].triangle.edges[0] = vec3_sub(triangle->tri_point[1], triangle->tri_point[0]);
		// mesh->triangle_data[index].triangle.edges[1] = vec3_sub(triangle->tri_point[2], triangle->tri_point[0]);
		index++;
	}
// 	triangle->colour = get_colour(&line);
}

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
	mesh->n_triangles = ascii_count_objects(fd, file_name);
	if (mesh->n_triangles == 0)
		ft_error(content_err);
    printf("number of triangles = %f\n", mesh->n_triangles);
	//TODO: create an array of vec3 or objects, parse the information in including normals, colour and material
	//render the frigging object, WHY IS THIS SO FRIGGING HARD
    mesh->triangle_data = malloc(mesh->n_triangles * sizeof(t_object));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
	create_mesh(mesh, fd);
	
	free(file_name);
	free(line);
    close(fd);
	exit(0); //
}
