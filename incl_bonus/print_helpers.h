/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:13:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 13:12:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_HELPERS_H
# define PRINT_HELPERS_H

# include "scene.h"
# include "shaders.h"
# include "stdio.h"

typedef union u_object			t_object;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_cylinder		t_cylinder;
typedef struct s_disk			t_disk;
typedef struct s_triangle		t_triangle;
typedef struct s_mesh			t_mesh;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_light			t_light;
typedef struct s_amb			t_amb;
typedef struct s_ray			t_ray;
typedef struct s_light_info	t_light_info;

void	print_sphere(t_object *obj);
void	print_plane(t_object *obj);
void	print_cylinder(t_object *obj);
void	print_triangle(t_object *obj);
void	print_disk(t_object *obj);
void	print_objs(t_object *obj);
void	print_ray(t_ray ray);
void	print_light(t_light light);
void	print_camera(t_camera cam);
void	print_scene(t_scene scene);
void	print_vec3(t_vec3 vec, char *label);
void	print_vec4(t_vec4 vec, char *label);
void	print_col(t_vec4 vec, char *label);
void	print_light_info(t_light_info light_info);
void	print_mesh(t_object *obj);
void	print_cone(t_object *obj);

#endif