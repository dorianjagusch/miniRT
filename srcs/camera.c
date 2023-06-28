/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:36:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/28 12:17:33 by djagusch         ###   ########.fr       */
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

/*Calculate the camera's basis vectors:

The forward vector is computed by subtracting the camera's position (scene->cam.pos) from its target (scene->cam.target).
It represents the direction the camera is facing.
The right vector is obtained by taking the cross product of the camera's up vector (scene->cam.up) and the forward vector.
It determines the rightward direction relative to the camera's orientation.
The up vector is calculated by crossing the forward vector with the right vector. It represents the upward direction relative to the camera's orientation.
Normalize the basis vectors:

To ensure that the basis vectors have a unit length, each of them is normalized using the vec3_normalize function. This step is essential for accurate transformations.
Construct the camera-to-world matrix:
The camera-to-world matrix is a 4x4 matrix represented by scene->cam.camera_to_world.
The first three columns of the matrix correspond to the right, up, and forward vectors, respectively.
The fourth column stores the camera's position, scene->cam.pos.
By constructing the camera-to-world matrix, you have a transformation matrix that allows you to convert points and vectors from camera space to world space
This matrix is then used in the create_primary_ray function to transform the ray direction from camera space to world space,
ensuring accurate mapping of coordinates in the ray-tracing process.*/

//responsible for constructing the camera-to-world matrix,
//which transforms points and vectors from camera space to world space

void camera_move(int key, t_img *img)
{
	if (key == MAIN_PAD_UP)
	{
		//img->scene.cam.look_at.z -= 0.1;
		img->scene.cam.zoom += 0.1;
	}
	if (key == MAIN_PAD_DOWN)
	{
		img->scene.cam.look_at.z -= 0.1;
	}
	if (key == MAIN_PAD_RIGHT)
	{
		img->scene.cam.look_at.x -= 0.1;
	}
	if (key == MAIN_PAD_LEFT)
	{
		img->scene.cam.look_at.x += 0.1;
	}
	render(img);
}

void	init_camera(t_camera *cam, t_vec3 pos, t_vec3 forward)
{
	t_vec3	dir_2d;

	cam->look_at = vec3_add(pos, vec3_multf(forward, cam->zoom));
	cam->right = vec3_cross(forward, (t_vec3){0, 1, 0});
	cam->up = vec3_cross(cam->right, forward);
	dir_2d = vec3_sub(pos, cam->look_at);
	dir_2d.y = 0;
	vec3_normalize(&dir_2d);
	cam->yaw = atan2(dir_2d.z, dir_2d.x);
	dir_2d = vec3_sub(pos, cam->look_at);
	dir_2d.x = 0;
	vec3_normalize(&dir_2d);
	cam->pitch = atan2(dir_2d.y, dir_2d.z);
}

t_vec3	get_direction_to_cam(t_camera *cam)
{
	t_vec3	yaw_pos;
	t_vec3	pitch_pos;
	t_vec3	dir;

	yaw_pos.x = cos(cam->yaw);
	yaw_pos.y = 0;
	yaw_pos.z = sin(cam->yaw);
	pitch_pos.x = 0;
	pitch_pos.y = sin(cam->pitch);
	pitch_pos.z = cos(cam->pitch);
	dir = vec3_add(yaw_pos, pitch_pos);
	vec3_normalize(&dir);
	return (dir);
}

t_vec3	get_camera_direction(t_camera *cam)
{
	t_vec3	dir;

	dir = vec3_multf(get_direction_to_cam(cam), -1.0);
	return (dir);
}

t_vec3	get_camera_position(t_camera *cam)
{
	t_vec3	pos;

	pos = vec3_multf(get_direction_to_cam(cam), cam->zoom);
	pos = vec3_add(pos, cam->look_at);
	return (pos);
}

t_ray	create_primary_ray(t_camera *cam, t_vec2 pxl)
{
	t_ray	primary_ray;
	double	norm_coord_x;
	double	norm_coord_y;

	norm_coord_x = (1.0 - (2.0 * (pxl.x + 0.5) / WIDTH)) * \
		cam->aspect_ratio * tan(M_PI_4);
	norm_coord_y = ((2.0 * (pxl.y + 0.5) / HEIGHT)) - 1.0 * tan(M_PI_4);
	primary_ray.origin = get_camera_position(cam);
	primary_ray.direction.x = cos(cam->yaw) * cos(cam->pitch) + norm_coord_x;
	primary_ray.direction.y = sin(cam->pitch) + norm_coord_y;
	primary_ray.direction.z = sin(cam->yaw) * cos(cam->pitch);
	vec3_normalize(&primary_ray.direction);
	return (primary_ray);
}
