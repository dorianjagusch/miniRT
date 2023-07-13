/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:58:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/13 11:30:44 by djagusch         ###   ########.fr       */
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
