
#include "minirt.h"
# include "objects.h"
# include "libft.h"

/*Because ASCII STL files can be very large, a binary version of STL exists.
A binary STL file has an 80-character header which is generally ignored,
but should never begin with the ASCII representation of the string solid,
as that may lead some software to confuse it with an ASCII STL file.
Following the header is a 4-byte little-endian unsigned integer indicating the number of
triangular facets in the file. Following that is data describing each triangle in turn.
The file simply ends after the last triangle.

Each triangle is described by twelve 32-bit floating-point numbers:
three for the normal and then three for the X/Y/Z coordinate of each vertex –
just as with the ASCII version of STL.
After these follows a 2-byte ("short") unsigned integer that is the "attribute byte count" – 
in the standard format, this should be zero because most software does not understand anything else.[9]

Floating-point numbers are represented as IEEE floating-point numbers and are assumed to be
little-endian, although this is not stated in documentation.*/

//https://en.wikipedia.org/wiki/STL_(file_format)

// typedef struct s_triangle
// {
// 	t_obj_e			type;
// 	t_vec3			tri_point[3];
// 	t_vec3			edges[2];
// 	t_vec4			colour;
// 	t_material_e	material;
// }					t_triangle;

// typedef struct s_range
// {
// 	float	min;
// 	float	max;
// }			t_range;

void set_triangle_data(t_object *triangle, t_triangle_data	data)
{
	// t_range	old;
	// t_range	new;

	// old.max = 50.0;
	// old.min = -60.0;

	// new.max = 10.0;
	// new.min = -10.0;

	triangle->triangle.type = triangle_obj;
	printf("\n----Printing data input----\n");
	printf("data.normal vector: x: %f	y: %f	z: %f\n", data.normal_vector[0], data.normal_vector[1], data.normal_vector[2]);
	triangle->triangle.normal.x = data.normal_vector[0];
	triangle->triangle.normal.y = data.normal_vector[1];
	triangle->triangle.normal.z = data.normal_vector[2];
	print_vec3(triangle->triangle.tri_point[0], "Normal: ");

	triangle->triangle.tri_point[0].x = data.vertex_a[0];
	triangle->triangle.tri_point[0].y = data.vertex_a[1];
	triangle->triangle.tri_point[0].z = data.vertex_a[2];
	printf("Data point A vector: x: %f	y: %f	z: %f\n", data.vertex_a[0], data.vertex_a[1], data.vertex_a[2]);
	print_vec3(triangle->triangle.tri_point[0], "point A");
	triangle->triangle.tri_point[1].x = data.vertex_b[0];
	triangle->triangle.tri_point[1].y = data.vertex_b[1];
	triangle->triangle.tri_point[1].z = data.vertex_b[2];
	printf("Data point B vector: x: %f	y: %f	z: %f\n", data.vertex_b[0], data.vertex_b[1], data.vertex_b[2]);
	print_vec3(triangle->triangle.tri_point[1], "point B");
	triangle->triangle.tri_point[2].x = data.vertex_c[0];
	triangle->triangle.tri_point[2].y = data.vertex_c[1];
	triangle->triangle.tri_point[2].z = data.vertex_c[2];
	printf("Data point C vector: x: %f	y: %f	z: %f\n", data.vertex_c[0], data.vertex_c[1], data.vertex_c[2]);
	print_vec3(triangle->triangle.tri_point[2], "point C");
	// vec3_scale(&triangle->triangle.normal, old, new);
	// vec3_scale(&triangle->triangle.tri_point[0], old, new);
	// vec3_scale(&triangle->triangle.tri_point[1], old, new);
	// vec3_scale(&triangle->triangle.tri_point[2], old, new);
	vec3_normalize(&triangle->triangle.normal);
	triangle->triangle.edges[0] = vec3_sub(triangle->triangle.tri_point[1], triangle->triangle.tri_point[0]);
	triangle->triangle.edges[1] = vec3_sub(triangle->triangle.tri_point[2], triangle->triangle.tri_point[0]);
	triangle->triangle.colour = (t_vec4) {1, 1, 0, 0};
// 	t_material_e	material;
}


void binary_parser(t_mesh *mesh, char *line)
{
    int             fd;
    t_stl_header    header;
    unsigned int    number_triangles;
	char			*file_name;
	t_triangle_data	data;
	int				index;

	line += 3;
	mesh->type = mesh_obj;
	file_name = *ft_split2(line);
    fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
    read(fd, &header,sizeof(t_stl_header));
	if (header.n_triangles == 0)
		ft_error(content_err);
	mesh->n_triangles = header.n_triangles;
    DEBUG_ONLY(printf("number of triangles = %d\n", header.n_triangles));
    mesh->triangle_data = malloc(mesh->n_triangles * sizeof(t_object));
	index = 0;
	while (index < mesh->n_triangles)
	{
		size_t bytes = read(fd, &data, sizeof(t_triangle_data));
		if (bytes <= 0)
			break ;
		printf("\n----Triangle # %i----\n", index);
		set_triangle_data(&mesh->triangle_data[index], data);
		index++;
	}
	free(file_name);
    close(fd);
}
