/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:40:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/06 00:47:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "float.h"

#define MIN 0
#define MAX 1
#define Y 0
#define Z 1
#define TOTAL 2

static void	fswap(double vals[2])
{
	double	temp;

	temp = vals[0];
	vals[0] = vals[1];
	vals[1] = temp;
}

void	sort_extremes(double cur_extr[2], double candidates[2])
{
	cur_extr[MIN] = fmax(cur_extr[MIN], candidates[MIN]);
	cur_extr[MAX] = fmin(cur_extr[MAX], candidates[MAX]);
}

void	dist_face(double res[2], double ray_dim, t_range range, double denom)
{
	res[MIN] = (range.min - ray_dim) * denom;
	res[MAX] = (range.max - ray_dim) * denom;
	if (denom < 0)
		fswap(res);
}

double	dist_box(const t_ray *ray, const t_object *obj)
{
	double	dist[3][2];
	t_vec3	denom;

	denom = vec3_inv(ray->direction);
	dist_face(dist[TOTAL], ray->origin.x,
		(t_range){obj->box.verts[MIN].x, obj->box.verts[MAX].x}, denom.x);
	dist_face(dist[Y], ray->origin.y,
		(t_range){obj->box.verts[MIN].y, obj->box.verts[MAX].y}, denom.y);
	if ((dist[TOTAL][MIN] > dist[Y][MAX])
		|| (dist[Y][MIN] > dist[TOTAL][MAX]))
		return (DBL_MAX);
	sort_extremes(dist[TOTAL], dist[Y]);
	dist_face(dist[Z], ray->origin.z,
		(t_range){obj->box.verts[MIN].z, obj->box.verts[MAX].z}, denom.z);
	if (denom.z < 0)
		fswap(dist[Z]);
	if ((dist[TOTAL][MIN] > dist[Z][MAX])
		|| (dist[Z][MIN] > dist[TOTAL][MAX]))
		return (DBL_MAX);
	sort_extremes(dist[TOTAL], dist[Z]);
	if (dist[TOTAL][MIN] > EPSILON)
		return (dist[TOTAL][MIN]);
	return (DBL_MAX);
}
