/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:13:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 14:15:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_HELPERS_H
# define PRINT_HELPERS_H

# include "minirt.h"

void	print_sphere(t_obj obj);
void	print_plane(t_obj obj);
void	print_cylinder(t_obj obj);
void	print_triangle(t_obj obj);
void	print_objs(t_obj obj);
void	print_light(t_light light);
void	print_camera(t_camera cam);
void	print_scene(t_scene scene);

#endif