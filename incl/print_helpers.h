/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:13:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 18:27:21 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_HELPERS_H
# define PRINT_HELPERS_H

# include "minirt.h"
# include "stdio.h"

void	print_sphere(t_object *obj);
void	print_plane(t_object *obj);
void	print_cylinder(t_object *obj);
void	print_triangle(t_object *obj);
void	print_disk(t_object *obj);
void	print_box(t_object *obj);
void	print_objs(t_object *obj);
void	print_ray(t_ray ray);
void	print_light(t_light light);
void	print_camera(t_camera cam);
void	print_scene(t_scene scene);
void	print_vec3(t_vec3 vec, char *label);
void	print_vec4(t_vec4 vec, char *label);
void	print_col(t_vec4 vec, char *label);
void	print_material(const t_material material);
void	print_light_info(t_light_info light_info);
void	print_mesh(t_object *obj);

#endif