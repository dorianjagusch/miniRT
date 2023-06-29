/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:36:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/27 14:03:17 by djagusch         ###   ########.fr       */
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

void camera_move(int key, t_img *img)
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

t_ray create_primary_ray(t_camera *cam, t_vec2 pxl)
{
	// TODO: why the hell does it render out objects position in opposite?
	t_ray primary_ray;
	double norm_coord_x;
	double norm_coord_y;

	norm_coord_x = (1.0 - (2.0 * (pxl.x + 0.5) / WIDTH)) * cam->aspect_ratio * tan(M_PI_4); // tan(cam->fov * DEG2RAD)
	norm_coord_y = ((2.0 * (pxl.y + 0.5) / HEIGHT) - 1.0) * tan(M_PI_4);
	// why does this not take into account the camera direction?
	primary_ray.origin = cam->pos;
	primary_ray.direction = vec3_sub((t_vec3){norm_coord_x, norm_coord_y, 1}, primary_ray.origin);
	vec3_normalize(&primary_ray.direction);
	return (primary_ray);
}

// t_ray create_primary_ray(t_camera *cam, t_vec2 pxl)
// {
//     t_ray primary_ray;
//     double norm_coord_x;
//     double norm_coord_y;

//     // Calculate normalized coordinates
//     norm_coord_x = (1.0 - (2.0 * (pxl.x + 0.5) / WIDTH)) * tan(M_PI_4);
//     norm_coord_y = ((2.0 * (pxl.y + 0.5) / HEIGHT) - 1.0) * tan(M_PI_4);

//     // Transform normalized coordinates based on camera orientation
//     t_vec3 camera_dir = vec3_normalize(cam->target - cam->pos);
//     t_vec3 camera_right = vec3_normalize(vec3_cross(camera_dir, cam->up));
//     t_vec3 camera_up = vec3_cross(camera_right, camera_dir);

//     primary_ray.origin = cam->pos;
//     primary_ray.direction = vec3_add3(
//         vec3_mult(camera_right, norm_coord_x),
//         vec3_mult(camera_up, norm_coord_y),
//         vec3_mult(camera_dir, 1.0)
//     );
//     vec3_normalize(&primary_ray.direction);

//     return primary_ray;
// }

