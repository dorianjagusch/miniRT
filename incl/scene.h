/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:19:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 15:17:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_math.h"
enum e_obj
{
	sphere,
	plane,
	cylinder,
	Ccmera,
	light,
	ambient
};

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	t_vec4	colour;
	int		valid;
}			t_light;

typedef struct s_camera
{
	t_vec3 	pos;
	t_vec3	direction;
	t_vec3 	right;
	t_vec3	up;
	double	aspect_ratio;
	double	fov;
	int		valid;
}			t_camera;

typedef struct s_amb
{
	double	ratio;
	t_vec4	colour;
	int		valid;
}			t_amb;

typedef struct s_obj
{
	int			type;
	t_vec3		position;
	t_vec3		normal;
	double		radius;
	double		radius2;
	double		height;
	t_vec4		colour;
	int			material;
}				t_obj;

typedef struct s_scene
{
	t_amb		amb;
	t_light		light;
	t_camera	cam;
	int32_t		bounces;
	t_obj		*objs;
	int			n_objs;

}				t_scene;

void	ft_skip_ws(char **line);
void	ft_skip_num(char **line, int mode);
t_vec4	get_colour(char **line);
double	get_double(char **line, int mode);
t_vec3	get_vec3(char **line);
void	validate_scene(t_scene *scene);

void	init_camera(t_camera *cam, t_vec3 pos, t_vec3 forward);
t_vec3	get_camera_direction(t_camera *cam);
t_vec3	get_camera_position(t_camera *cam);
t_vec3	get_direction_to_cam(t_camera *cam);

#endif