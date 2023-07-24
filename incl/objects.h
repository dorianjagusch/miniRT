/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:42:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 13:09:16 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "scene.h"
# include "patterns.h"

typedef union u_object	t_object;

typedef enum e_obj
{
	sphere_obj,
	plane_obj,
	cylinder_obj,
	disk_obj,
}	t_obj_e;

typedef struct s_sphere
{
	t_obj_e			type;
	t_texture		*texture;
	t_vec4			colour;
	t_vec3			pos;
	float			radius;
	float			radius2;
}					t_sphere;

typedef struct s_plane
{
	t_obj_e			type;
	t_texture		*texture;
	t_vec4			colour;
	t_vec3			pos;
	t_vec3			normal;
	float			d;
	int				isvisible;
}					t_plane;

typedef struct s_cylinder
{
	t_obj_e			type;
	t_texture		*texture;
	t_vec4			colour;
	t_vec3			pos;
	t_object		*top;
	t_object		*bottom;
	float			radius;
	float			radius2;
	int				disk_hit;
	t_vec3			normal;
	float			height;
}					t_cylinder;

typedef struct s_disk
{
	t_obj_e			type;
	t_texture		*texture;
	t_vec4			colour;
	t_vec3			pos;
	t_vec3			normal;
	float			d;
	float			radius;
	int				isvisible;
}					t_disk;

typedef union u_object
{
	t_obj_e		type;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_disk		disk;
}				t_object;

#endif