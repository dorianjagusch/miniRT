/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:36:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 13:41:44 by djagusch         ###   ########.fr       */
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
void	calculate_rotation_angles(t_img *img, int delta[X], int delta_y)
{
	float	fov_rad[2];
	float	norm_delta[2];
	float	angle[2];

	fov_rad[X] = img->scene.cam.fov * DEG2RAD;
	fov_rad[Y] = atan(tan(fov_rad[X] / 2.0) / img->aspect_ratio) * 2.0;
	norm_delta[X] = (2.0 * delta[X]) / WIDTH - 1.0;
	norm_delta[Y] = 1.0 - (2.0 * delta[Y]) / HEIGHT;
	angle[X] = norm_delta[X] * fov_rad[X];
	angle[Y] = norm_delta[Y] * fov_rad[Y];
	t_mat4 rotation[X] = mat4_rotate(angle[Y]);
	img->scene.cam.dir = mat4_mul_vec3(rotation[X], img->scene.cam.dir);
	img->scene.cam.up = mat4_mul_vec3(rotation[X], img->scene.cam.up);
	t_mat4 rotation[Y] = mat4_rotate(angle[X]);
	img->scene.cam.dir = mat4_mul_vec3(rotation[Y], img->scene.cam.dir);
	img->scene.cam.up = mat4_mul_vec3(rotation[Y], img->scene.cam.up);

	vec3_normalize(&img->scene.cam.dir);
	vec3_normalize(&img->scene.cam.up);
}

// t_ray	create_primary_ray(t_camera *cam, t_vec2 pxl)
// {
// 	t_ray	primary_ray;
// 	float	norm_coord[X;
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
	t_ray	primary_ray;
	float	norm_coord_x = (1.0f - (2.0f * (pxl.x + 0.5f) / WIDTH)) * cam->aspect_ratio * tan(cam->fov * DEG2RAD);
	float	norm_coord_y = (1.0f - (2.0f * (pxl.y + 0.5f) / HEIGHT)) * tan(cam->fov * DEG2RAD);

	float r = sqrt(norm_coord_x * norm_coord_x + norm_coord_y * norm_coord_y);
	float phi = atan2(norm_coord_y, norm_coord_x);

	float fisheye_r = r * 0.5f;//cam->fisheye_factor;
	float fisheye_x = fisheye_r * cos(phi);
	float fisheye_y = fisheye_r * sin(phi);

	cam->right = vec3_cross(cam->dir, cam->up);
	vec3_normalize(&cam->right);
	cam->up = vec3_cross(cam->right, cam->dir);

	primary_ray.origin = cam->pos;
	primary_ray.direction = vec3_add(cam->dir,
		vec3_add(vec3_multf(cam->right, fisheye_x),
			vec3_multf(cam->up, fisheye_y)));
	vec3_normalize(&primary_ray.direction);

	return (primary_ray);
}
