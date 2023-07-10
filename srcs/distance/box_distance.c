/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:58:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/10 16:49:09 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "float.h"

#define MIN 0
#define MAX 1
#define Y 0
#define Z 1
#define TOTAL 2

// static void	fswap(float vals[2])
// {
// 	float	temp;

// 	temp = vals[0];
// 	vals[0] = vals[1];
// 	vals[1] = temp;
// }

// void	sort_extremes(float cur_extr[2], float candidates[2])
// {
// 	cur_extr[MIN] = fmax(cur_extr[MIN], candidates[MIN]);
// 	cur_extr[MAX] = fmin(cur_extr[MAX], candidates[MAX]);
// }

// void	dist_face(float res[2], float ray_dim, t_range range, float denom)
// {
// 	DEBUG_ONLY(printf("obj->Box.enom\n", denom));
// 	DEBUG_ONLY(printf("obj->Box.in %", ray_dim));
// 	res[MIN] = (range.min - ray_dim) * denom;
// 	res[MAX] = (range.max - ray_dim) * denom;
// 	DEBUG_ONLY(printf("Box current min %f\n", res[MIN]));
// 	DEBUG_ONLY(printf("Box current max %f\n", res[MAX]));
// 	if (denom < 0)
// 		fswap(res);
// 	DEBUG_ONLY(printf("Box after swap %f\n", res[MIN]));
// 	DEBUG_ONLY(printf("Box after swap %f\n", res[MAX]));
// }

// float	dist_box(const t_ray *ray, t_object *obj)
// {
// 	float	dist[3][2];
// 	t_vec3	denom;

// 	denom = vec3_inv(ray->direction);
// 	dist_face(dist[TOTAL], ray->origin.x,
// 		(t_range){obj->box.verts[MIN].x, obj->box.verts[MAX].x}, denom.x);
// 	// DEBUG_ONLY(printf("Box x distance %f\n", dist[TOTAL][MIN]));
// 	// DEBUG_ONLY(printf("Box x distance %f\n", dist[TOTAL][MAX]));
// 	dist_face(dist[Y], ray->origin.y,
// 		(t_range){obj->box.verts[MIN].y, obj->box.verts[MAX].y}, denom.y);
// 	DEBUG_ONLY(printf("Box point min y %f\n", obj->box.verts[MIN].y));
// 	DEBUG_ONLY(printf("Box point max y %f\n", obj->box.verts[MAX].y));
// 	DEBUG_ONLY(printf("Box y distance %f\n", dist[Y][MIN]));
// 	DEBUG_ONLY(printf("Box y distance %f\n", dist[Y][MAX]));
// 	if ((dist[TOTAL][MIN] > dist[Y][MAX])
// 		|| (dist[Y][MIN] > dist[TOTAL][MAX]))
// 		return (FLT_MAX);
// 	sort_extremes(dist[TOTAL], dist[Y]);
// 	dist_face(dist[Z], ray->origin.z,
// 		(t_range){obj->box.verts[MIN].z, obj->box.verts[MAX].z}, denom.z);
// 	DEBUG_ONLY(printf("Box y distance %f\n", dist[Z][MIN]));
// 	DEBUG_ONLY(printf("Box y distance %f\n", dist[Z][MAX]));
// 	if (denom.z < 0)
// 		fswap(dist[Z]);
// 	if ((dist[TOTAL][MIN] > dist[Z][MAX])
// 		|| (dist[Z][MIN] > dist[TOTAL][MAX]))
// 		return (FLT_MAX);
// 	sort_extremes(dist[TOTAL], dist[Z]);
// 	DEBUG_ONLY(printf("Box distance %f\n", dist[TOTAL][MIN]));
// 	if (dist[TOTAL][MIN] > EPSILON)
// 		return (dist[TOTAL][MIN]);
// 	return (FLT_MAX);
// }

static void	get_box_normal(t_vec3 *normal, float dist, t_vec3 face_dist[2])
{
	if (fabs(dist - face_dist[MIN].x) < EPSILON)
		*normal = (t_vec3){-1, 0, 0};
	else if (fabs(dist - face_dist[MIN].y) < EPSILON)
		*normal = (t_vec3){0, -1, 0};
	else if (fabs(dist - face_dist[MIN].z) < EPSILON)
		*normal = (t_vec3){0, 0, -1};
	else if (fabs(dist - face_dist[MAX].x) < EPSILON)
		*normal = (t_vec3){1, 0, 0};
	else if (fabs(dist - face_dist[MAX].y) < EPSILON)
		*normal = (t_vec3){0, 1, 0};
	else if (fabs(dist - face_dist[MAX].z) < EPSILON)
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
	if (dist[MIN] > dist[MAX] || dist[MIN] < EPSILON)
		return (FLT_MAX);
	return (dist[MIN]);
}

t_vec3	get_pos_min(const t_ray *ray, const t_plane2 planes[6], float dist[3])
{
	int		i;
	float	params[2];
	int		index;

	i = -1;
	while (++i < 6)
	{
		params[0] = planes[i].distance - vec3_dot(planes[i].normal,
				ray->origin);
		params[1] = vec3_dot(planes[i].normal, ray->direction);
		if (fabsf(params[1]) < EPSILON)
		{
			if (params[0] < 0.0)
				dist[MIN] = FLT_MAX;
		}
		else
		{
			dist[TOTAL] = params[0] / params[1];
			if (params[1] < 0.0)
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
	return (planes[index].normal);
}

float	dist_arbbox(const t_ray *ray, t_object *obj)
{
	t_vec3		denom;
	float		dist[3];
	int			i;

	denom = vec3_inv(ray->direction);
	i = -1;
	dist[MIN] = FLT_MIN;
	dist[MAX] = FLT_MAX;
	obj->arbbox.normal = get_pos_min(ray, obj->arbbox.planes, dist);
	if (dist[MIN] > dist[MAX] || dist[MAX] < 0.0 || dist[MIN] == FLT_MAX)
		return (FLT_MAX);
	dist[MIN] = fmaxf(dist[MIN], 0.0);
	return (dist[MIN]);
}
