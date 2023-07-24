/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/24 16:00:12 by smorphet         ###   ########.fr       */
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

#ifndef X
# define X 0
#endif
#ifndef Y
# define Y 1
#endif
#ifndef R
# define R 2
#endif

void	camera_move(int key, t_img *img)
{
	if (key == MAIN_PAD_UP)
		img->scene.cam.pos.z += 0.501;
	if (key == MAIN_PAD_DOWN)
		img->scene.cam.pos.z -= 0.501;
	if (key == MAIN_PAD_RIGHT)
		img->scene.cam.pos.x += 0.501;
	if (key == MAIN_PAD_LEFT)
		img->scene.cam.pos.x -= 0.501;
	if (key == MAIN_PAD_W)
		img->scene.cam.pos.y += 0.501;
	if (key == MAIN_PAD_S)
		img->scene.cam.pos.y -= 0.501;
	if (key == MAIN_PAD_D)
		img->scene.cam.dir.x += 1;
	if (key == MAIN_PAD_A)
		img->scene.cam.dir.x -= 1;
	render(img);
}

t_ray	create_primary_ray(t_camera *cam, t_vec2 pxl)
{
	float	norm_coord_x;
	float	norm_coord_y;
	t_ray	primary_ray;
	float	fisheye[3];
	float	phi;

	norm_coord_x = (1.0f - (2.0f * (pxl.x + 0.5f) / WIDTH)) * \
		cam->aspect_ratio * tan(cam->fov * DEG2RAD);
	norm_coord_y = (1.0f - (2.0f * (pxl.y + 0.5f) / HEIGHT)) * \
		tan(cam->fov * DEG2RAD);

	fisheye[R] = sqrt(norm_coord_x * norm_coord_x + norm_coord_y * norm_coord_y);
	phi = atan2(norm_coord_y, norm_coord_x);

	fisheye[R] = fisheye[R] * 0.1f;
	fisheye[X] = fisheye[R] * cos(phi);
	fisheye[Y] = fisheye[R] * sin(phi);
	primary_ray.origin = cam->pos;
	primary_ray.direction = vec3_add(cam->dir,
			vec3_add(vec3_multf(cam->right, fisheye[X]),
				vec3_multf(cam->up, fisheye[Y])));
	vec3_normalize(&primary_ray.direction);
	return (primary_ray);
}
