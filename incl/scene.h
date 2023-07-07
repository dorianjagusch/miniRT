/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:19:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 23:44:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_math.h"
# include "objects.h"

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	t_vec4	colour;
	int		valid;
}			t_light;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	right;
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

typedef struct s_scene
{
	t_amb		amb;
	t_light		light;
	t_camera	cam;
	int32_t		bounces;
	t_object	*objs;
	int			n_objs;

}				t_scene;

void	ft_skip_ws(char **line);
void	ft_skip_num(char **line, int mode);
t_vec4	get_colour(char **line);
double	get_double(char **line, int mode);
t_vec3	get_vec3(char **line);
void	validate_scene(t_scene *scene);
void	create_sphere(t_sphere *sphere, char *line);
void	create_cylinder(t_cylinder *cylinder, char *line);
void	create_plane(t_plane *plane, char *line);
void	create_disk(t_disk *disk, char *line);
void	create_triangle(t_triangle *triangle, char *line);
void	create_box(t_box *box, char *line);

#endif