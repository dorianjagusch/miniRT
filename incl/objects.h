/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:42:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 14:52:52 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "scene.h"
# include "materials.h"

typedef enum e_obj
{
	sphere_obj,
	plane_obj,
	cylinder_obj,
	disk_obj,
	triangle_obj,
	box_obj,
	mesh_obj,
}	t_obj_e;

typedef struct s_sphere
{
	t_obj_e			type;
	t_vec3			pos;
	double			radius;
	double			radius2;
	t_vec4			colour;
	t_material_e	material;
}					t_sphere;


typedef struct s_plane
{
	t_obj_e			type;
	t_vec3			pos;
	t_vec3			normal;
	double			d;
	t_vec4			colour;
	t_material_e	material;
}					t_plane;

typedef struct s_cylinder
{
	t_obj_e			type;
	t_vec3			pos;
	double			radius;
	double			radius2;
	t_vec3			normal;
	double			height;
	t_vec4			colour;
	t_material_e	material;
}			t_cylinder;

typedef struct s_disk
{
	t_obj_e			type;
	t_vec3			pos;
	t_vec3			normal;
	double			d;
	double			radius;
	t_vec4			colour;
	t_material_e	material;
}					t_disk;

typedef struct s_triangle
{
	t_obj_e			type;
	t_vec3			tri_point[3];
	t_vec3			edges[2];
	t_vec4			colour;
	t_material_e	material;
}					t_triangle;

typedef struct s_mesh
{
	t_obj_e			type;
	double			n_triangles;
	t_vec3			*vertices; //need to malloc this
}					t_mesh;

typedef struct s_stl_header //TODO: can this stay here, norm compliance?
{
    unsigned char metadata[80]; //80bytes - this is the header file all binarys have (diposable data)
    unsigned int n_triangles;   //4bytes
}   t_stl_header;

typedef struct s_stl_data //TODO: can this stay here, norm compliance?
{   
    float  normal_vector[3];	//12 bytes
    float  vertex_a[3];			//12 bytes
    float  vertex_b[3];			//12 bytes
    float  vertex_c[3];			//12 bytes
    unsigned short  att;	//2 bytes (disposable data)
} 		t_triangle_data;

typedef struct s_box
{
	t_obj_e			type;
	t_vec3			verts[2];
	t_vec4			colour;
	t_material_e	material;
}					t_box;

typedef union u_object
{
	t_obj_e		type;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_disk		disk;
	t_triangle	triangle;
	t_box		box;
	t_mesh		mesh;
}				t_object;

#endif