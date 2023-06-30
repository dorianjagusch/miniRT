/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:36:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/30 12:23:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

#ifndef M_PI_4
# define M_PI_4 0.78539816339744830962
#endif
#ifndef DEG2RAD
# define DEG2RAD 0.008726646259971647737
#endif

//responsible for constructing the camera-to-world matrix,
//which transforms points and vectors from camera space to world space

void	camera_move(int key, t_img *img)
{
	if (key == MAIN_PAD_UP)
	{
		img->scene.cam.pos.z -= 0.1;
	}
	if (key == MAIN_PAD_DOWN)
	{
		img->scene.cam.pos.z += 0.1;
	}
	if (key == MAIN_PAD_RIGHT)
	{
		img->scene.cam.pos.x -= 0.1;
	}
	if (key == MAIN_PAD_LEFT)
	{
		img->scene.cam.pos.x += 0.1;
	}
	render(img);
}

t_ray	create_primary_ray(t_camera *cam, t_vec2 pxl)
{
	t_ray	primary_ray;
	double	norm_coord_x;
	double	norm_coord_y;

	norm_coord_x = (1 - (2.0 * (WIDTH - (pxl.x + 0.5)) / WIDTH)) * \
	cam->aspect_ratio * tan(M_PI_4);
	norm_coord_y = ((2.0 * (pxl.y + 0.5) / HEIGHT) - 1) * tan(M_PI_4);
	primary_ray.origin = cam->pos;
	primary_ray.direction = vec3_sub((t_vec3){cam->direction.x + norm_coord_x,
			cam->direction.y + norm_coord_y,
			cam->direction.z},
			primary_ray.origin);
	vec3_normalize(&primary_ray.direction);
	return (primary_ray);
}
