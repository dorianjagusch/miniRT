/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:19:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 16:55:05 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"

enum e_obj
{
	sphere,
	plane,
	cylinder,
	Camera,
	Light,
	Ambient
};

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	int32_t	colour;
}			t_light;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
}			t_camera;

typedef struct s_amb
{
	double	ratio;
	int32_t	colour;
}			t_amb;

typedef struct s_obj
{
	int		type;
	t_vec3	position;
	t_vec3	normal;
	double	radius;
	double	height;
	int32_t	material;
	double	metallicity;
	int32_t	colour;
}			t_obj;

typedef struct s_scene
{
	t_amb		amb;
	t_light		light;
	t_camera	cam;
	int32_t		bounces;
	t_obj		*objs;
	int			n_objs;

} t_scene;

typedef struct s_dist_func
{
	int	type;
	int	(*dist_funct)(t_obj, t_camera);
} t_dist_func;


void	ft_skip_ws(char **line);
int		ft_skip_num(char **line, int mode);
int		get_colour(char **line);
double	get_double(char **line, int mode);
t_vec3	get_vec3(char **line);

#endif