/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:42:44 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/07 17:59:44 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define U 0
#define V 1
#define PVEC 0
#define TVEC 1
#define QVEC 2

/*The Möller-Trumbore algorithm is an efficient method for ray-triangle
intersection testing. It is widely used in computer graphics and ray tracing
to determine whether a given ray intersects a triangle and, if so, compute the
intersection point.

In the Möller-Trumbore algorithm, after calculating the parameter u, which
represents the intersection point's barycentric coordinate relative to the
triangle's first edge, the parameter v is calculated to determine the
intersection point's barycentric coordinate relative to the triangle's
second edge.
If v is less than 0 or u + v is greater than 1, it indicates that the
intersection point is outside the triangle,
and the function returns 0.0, indicating no intersection. Otherwise,
if the conditions are satisfied, v represents the intersection point's
barycentric coordinate relative to the triangle's second edge.
In summary, v is a parameter used in the algorithm to determine if the
intersection point lies within the triangle or not.
*/

float	dist_triangle(const t_ray *ray, t_object *obj)
{
	float	det;
	float	inv_det;
	t_vec3	bary_vec[3];
	float	bary_weights[2];

	bary_vec[PVEC] = vec3_cross(ray->direction, obj->triangle.edges[1]);
	det = vec3_dot(obj->triangle.edges[0], bary_vec[PVEC]);
	if (fabs(det) < EPSILON)
		return (FLT_MAX);
	inv_det = 1.0 / det;
	bary_vec[TVEC] = vec3_sub(ray->origin, obj->triangle.tri_point[0]);
	bary_weights[U] = vec3_dot(bary_vec[TVEC], bary_vec[PVEC]) * inv_det;
	if (bary_weights[U] < 0.0 || bary_weights[U] > 1.0)
		return (FLT_MAX);
	bary_vec[QVEC] = vec3_cross(bary_vec[TVEC], obj->triangle.edges[0]);
	bary_weights[V] = vec3_dot(ray->direction, bary_vec[QVEC]) * inv_det;
	if (bary_weights[V] < 0.0 || (bary_weights[U] + bary_weights[V]) > 1.0)
		return (FLT_MAX);
	return (vec3_dot(obj->triangle.edges[1], bary_vec[QVEC]) * inv_det);
}
