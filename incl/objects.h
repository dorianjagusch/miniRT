/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:42:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 09:56:46 by djagusch         ###   ########.fr       */
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
	t_vec3			verts[3];
	t_vec3			edges[2];
	t_vec4			colour;
	t_material_e	material;
}					t_triangle;

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
}				t_object;

#endif