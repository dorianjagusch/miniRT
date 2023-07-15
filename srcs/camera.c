/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:36:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 14:42:41 by djagusch         ###   ########.fr       */
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

// void	calculate_rotation_angles(t_img *img, int delta_x, int delta_y)
// {
// 	float	fov_rad[2];
// 	float	norm_delta[2];
// 	float	angle[2];
// 	t_mat4	rotation_x;
// 	t_mat4	rotation_y;

// 	fov_rad[X] = img->scene.cam.fov * DEG2RAD;
// 	fov_rad[Y] = atan(tan(fov_rad[X] / 2.0) / img->aspect_ratio) * 2.0;
// 	norm_delta[X] = (2.0 * delta_x) / WIDTH - 1.0;
// 	norm_delta[Y] = 1.0 - (2.0 * delta_y) / HEIGHT;
// 	angle[X] = norm_delta[X] * fov_rad[X];
// 	angle[Y] = norm_delta[Y] * fov_rad[Y];
// 	rotation_x = mat4_rotate_x(angle[Y]);
// 	img->scene.cam.dir = mat4_mult_vec3(rotation_x, img->scene.cam.dir);
// 	img->scene.cam.up = mat4_mult_vec3(rotation_x, img->scene.cam.up);
// 	rotation_y = mat4_rotate_y(angle[X]);
// 	img->scene.cam.dir = mat4_mult_vec3(rotation_y, img->scene.cam.dir);
// 	img->scene.cam.up = mat4_mult_vec3(rotation_y, img->scene.cam.up);
// 	vec3_normalize(&img->scene.cam.dir);
// 	vec3_normalize(&img->scene.cam.up);
// 	render(img);
// }

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

	fisheye[R]= sqrt(norm_coord_x * norm_coord_x + norm_coord_y * norm_coord_y);
	phi = atan2(norm_coord_y, norm_coord_x);

	fisheye[R]= fisheye[R]* 0.5f;
	fisheye[X] = fisheye[R]* cos(phi);
	fisheye[Y] = fisheye[R]* sin(phi);
	primary_ray.origin = cam->pos;
	primary_ray.direction = vec3_add(cam->dir,
	vec3_add(vec3_multf(cam->right, fisheye[X]),
	vec3_multf(cam->up, fisheye[Y])));
	vec3_normalize(&primary_ray.direction);
	return (primary_ray);
}
