/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:36:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/14 10:07:01 by djagusch         ###   ########.fr       */
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

// t_ray	create_primary_ray(t_camera *cam, t_vec2 pxl)
// {
// 	t_ray	primary_ray;
// 	float	norm_coord_x;
// 	float	norm_coord_y;

// 	norm_coord_x = (1.0f - (2.0f * (pxl.x + 0.5f) / WIDTH)) * cam->aspect_ratio * tan(cam->fov * DEG2RAD);
// 	norm_coord_y = (1.0f - (2.0f * (pxl.y + 0.5f) / HEIGHT)) * tan(cam->fov * DEG2RAD);
// 	primary_ray.origin = cam->pos;
// 	primary_ray.direction = vec3_add(cam->dir,
// 		vec3_add(vec3_multf(cam->right, norm_coord_x),
// 			vec3_multf(cam->up, norm_coord_y)));
// 	vec3_normalize(&primary_ray.direction);
// 	return (primary_ray);
// }

t_ray	create_primary_ray(t_camera *cam, t_vec2 pxl)
{
	t_ray primary_ray;
	float norm_coord_x = (1.0f - (2.0f * (pxl.x + 0.5f) / WIDTH)) * cam->aspect_ratio * tan(cam->fov * DEG2RAD);
	float norm_coord_y = (1.0f - (2.0f * (pxl.y + 0.5f) / HEIGHT)) * tan(cam->fov * DEG2RAD);

	float r = sqrt(norm_coord_x * norm_coord_x + norm_coord_y * norm_coord_y);
	float phi = atan2(norm_coord_y, norm_coord_x);

	float fisheye_r = r * 0.5f;//cam->fisheye_factor;
	float fisheye_x = fisheye_r * cos(phi);
	float fisheye_y = fisheye_r * sin(phi);

	cam->right = vec3_cross(cam->dir, cam->up);
	vec3_normalize(&cam->right);
	cam->up = vec3_cross(cam->right, cam->dir);

	primary_ray.origin = cam->pos;
	primary_ray.direction = vec3_add(cam->dir, vec3_add(vec3_multf(cam->right, fisheye_x), vec3_multf(cam->up, fisheye_y)));
	vec3_normalize(&primary_ray.direction);

	return primary_ray;
}
