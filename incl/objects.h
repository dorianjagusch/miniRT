/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:42:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/17 10:59:11 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "scene.h"
# include "materials.h"

typedef union u_object	t_object;

typedef enum e_obj
{
	sphere_obj,
	plane_obj,
	cylinder_obj,
	disk_obj,
	triangle_obj,
	box_obj,
	mesh_obj,
	cone_obj,
}	t_obj_e;

typedef struct s_sphere
{
	t_obj_e			type;
	t_vec3			pos;
	float			radius;
	float			radius2;
	t_vec4			colour;
	t_material_e	material;
}					t_sphere;


typedef struct s_plane
{
	t_obj_e			type;
	t_vec3			pos;
	t_vec3			normal;
	float			d;
	int				isvisible;
	t_vec4			colour;
	t_material_e	material;
}					t_plane;

typedef struct s_cylinder
{
	t_obj_e			type;
	t_vec3			pos;
	t_object		*top;
	t_object		*bottom;
	float			radius;
	float			radius2;
	int				disk_hit;
	t_vec3			normal;
	float			height;
	t_vec4			colour;
	t_material_e	material;
}					t_cylinder;

typedef struct s_disk
{
	t_obj_e			type;
	t_vec3			pos;
	t_vec3			normal;
	float			d;
	float			radius;
	int				isvisible;
	t_vec4			colour;
	t_material_e	material;
}					t_disk;

typedef struct s_triangle
{
	t_obj_e			type;
	t_vec3			tri_point[3];
	t_vec3			normal;
	t_vec3			edges[2];
	t_vec4			colour;
	t_material_e	material;
}					t_triangle;

typedef struct s_mesh
{
	t_obj_e			type;
	float			n_triangles;
	float			count_v;
	float			count_vn;
	float			count_vt;
	float			count_f;
	t_vec3			*vertex;
	t_vec3			*normals;
	t_vec2			*textures;
	t_vec3_face		**faces;
	t_vec4			colour;
	int				obj_id;
	t_material_e	material;
	t_object		*triangle_data;
}					t_mesh;

typedef struct s_box
{
	t_obj_e			type;
	t_vec3			verts[2];
	t_vec3			normal;
	t_vec4			colour;
	t_material_e	material;
}					t_box;

typedef struct s_cone
{
	t_obj_e			type;
	t_vec3			pos;
	t_vec3			center;
	t_object		*bottom;
	float			radius;
	float			angle;
	int				disk_hit;
	t_vec3			normal;
	float			height;
	t_vec4			colour;
	t_material_e	material;
}					t_cone;


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
	t_cone		cone;
}				t_object;


#endif