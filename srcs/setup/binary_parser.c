
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

// foreach triangle                      - 50 bytes:
//     REAL32[3] – Normal vector             - 12 bytes
//     REAL32[3] – Vertex 1                  - 12 bytes
//     REAL32[3] – Vertex 2                  - 12 bytes
//     REAL32[3] – Vertex 3                  - 12 bytes
//     UINT16    – Attribute byte count      -  2 bytes
// end


// typedef struct s_stl_header //TODO: can this stay here, norm compliance?
// {
//     unsigned char metadata[80]; //80bytes - this is the header file all binarys have (diposable data)
//     unsigned int n_triangles;   //4bytes
// }   t_stl_header;

// typedef struct s_triangle_data //TODO: can this stay here, norm compliance?
// {   
//     float  normal_vector[3];   //12 bytes
//     float  vertex_a[3];   //12 bytes
//     float  vertex_b[3];   //12 bytes
//     float  vertex_c[3];   //12 bytes
//     unsigned short  att;       //2 bytes (disposable data)
// } 		t_triangle_data;

void binary_parser(t_mesh *mesh, char *line)
{
    printf("found binary_set_scene\n");
    int             fd;
    t_stl_header    header;
    unsigned int    number_triangles;
	char			*file_name;
	t_triangle_data	data;
	int				index;

	line += 3;
	file_name = *ft_split2(line);
    fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(errno);
    read(fd, &header,sizeof(t_stl_header));
	if (header.n_triangles == 0)
		ft_error(content_err);
	mesh->n_triangles = header.n_triangles;
    DEBUG_ONLY(printf("number of triangles = %d\n", header.n_triangles));
    mesh->vertices = malloc(mesh->n_triangles * sizeof(t_triangle_data));
	index = 0;
	while (index < mesh->n_triangles)
	{
		read(fd, &data,sizeof(t_triangle_data));
		mesh->vertices[index] = data;
		DEBUG_ONLY(print_vec3(mesh->vertices->normal_vector, "Normal"));
		DEBUG_ONLY(print_vec3(mesh->vertices->vertex_a, "Vertex a"));
		DEBUG_ONLY(print_vec3(mesh->vertices->vertex_b, "Vertex b"));
		DEBUG_ONLY(print_vec3(mesh->vertices->vertex_c, "Vertex c"));
		index++;
	}
	
	free(file_name);
    close(fd);
    exit (0);//
}
