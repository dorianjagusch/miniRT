/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:58:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/12 16:06:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "float.h"

#define MIN 0
#define MAX 1
#define Y 0
#define Z 1
#define TOTAL 2

static void	get_box_normal(t_vec3 *normal, float dist, t_vec3 face_dist[2])
{
	if (fabsf(dist - fabsf(face_dist[MIN].x)) < EPSILON)
		*normal = (t_vec3){-1, 0, 0};
	else if (fabsf(dist - fabsf(face_dist[MIN].y)) < EPSILON)
		*normal = (t_vec3){0, -1, 0};
	else if (fabsf(dist - fabsf(face_dist[MIN].z)) < EPSILON)
		*normal = (t_vec3){0, 0, -1};
	else if (fabsf(dist - fabsf(face_dist[MAX].x)) < EPSILON)
		*normal = (t_vec3){1, 0, 0};
	else if (fabsf(dist - fabsf(face_dist[MAX].y)) < EPSILON)
		*normal = (t_vec3){0, 1, 0};
	else if (fabsf(dist - fabsf(face_dist[MAX].z)) < EPSILON)
		*normal = (t_vec3){0, 0, 1};
}

float	dist_box(const t_ray *ray, t_object *obj)
{
	t_vec3	face_dist[2];
	float	dist[2];
	t_vec3	denom;

	denom = vec3_inv(ray->direction);
	face_dist[MIN] = vec3_compmult(vec3_sub(obj->box.verts[MIN], ray->origin),
			denom);
	face_dist[MAX] = vec3_compmult(vec3_sub(obj->box.verts[MAX], ray->origin),
			denom);
	dist[MIN] = fmaxf(fmaxf(fminf(face_dist[MIN].x, face_dist[MAX].x),
				fminf(face_dist[MIN].y, face_dist[MAX].y)),
			fminf(face_dist[MIN].z, face_dist[MAX].z));
	dist[MAX] = fminf(fminf(fmaxf(face_dist[MIN].x, face_dist[MAX].x),
				fmaxf(face_dist[MIN].y, face_dist[MAX].y)),
			fmaxf(face_dist[MIN].z, face_dist[MAX].z));
	get_box_normal(&obj->box.normal, dist[MIN], face_dist);
	if (dist[MIN] < dist[MAX] && dist[MIN] > EPSILON)
		return (dist[MIN]);
	if (dist[MIN] < dist[MAX] && dist[MAX] > EPSILON)
		return (dist[MAX]);
	return (FLT_MAX);
}

int	get_pos_min(const t_ray *ray, const t_plane2 planes[6], float dist[3])
{
	int		i;
	float	params[2];
	int		index;

	i = -1;
	index = 6;
	while (++i < 6)
	{
		params[0] = planes[i].distance - vec3_dot(planes[i].normal,
				ray->origin);
		params[1] = vec3_dot(planes[i].normal, ray->direction);
		if (fabsf(params[1]) < EPSILON)
		{
			if (params[0] < EPSILON)
				dist[MIN] = FLT_MAX;
		}
		else
		{
			dist[TOTAL] = params[0] / params[1];
			if (params[1] < EPSILON)
				if (dist[TOTAL] > dist[MIN])
				{
					dist[MIN] = dist[TOTAL];
					index = i;
				}
			// else
			// 	if (dist[TOTAL] < dist[MAX])
			// 		dist[MAX] = dist[TOTAL];
		}
		if (dist[MIN] > dist[MAX])
			dist[MIN] = FLT_MAX;
	}
	return (index);
}

float	dist_arbbox(const t_ray *ray, t_object *obj)
{
	t_vec3		denom;
	float		dist[3];
	int			index;

	denom = vec3_inv(ray->direction);
	dist[MIN] = FLT_MIN;
	dist[MAX] = FLT_MAX;
	index = get_pos_min(ray, obj->arbbox.planes, dist);
	if (index < 6)
		obj->arbbox.normal = obj->arbbox.planes[index].normal;
	if (dist[MIN] > dist[MAX] || dist[MAX] < EPSILON
		|| dist[MIN] == FLT_MAX)
		return (FLT_MAX);
	dist[MIN] = fmaxf(dist[MIN], 0.0);
	return (dist[MIN]);
}
