/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:42:44 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/05 19:30:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"
#define U 0
#define V 1

/*The Möller-Trumbore algorithm is an efficient method for ray-triangle intersection testing. It is widely used in computer graphics and ray tracing to determine whether a given ray intersects a triangle and, if so, compute the intersection point.

The algorithm is based on the concept of barycentric coordinates,
which represent a point within a triangle as a linear combination of the triangle's vertices.

Here's a step-by-step explanation of the Möller-Trumbore algorithm:
Input: The algorithm takes as input a ray (defined by an origin point and a direction vector)
		and a triangle (defined by its three vertices).
Compute the triangle's normal: Calculate the triangle's normal vector by taking the cross product of two of its edges.
		This step assumes the triangle's vertices are defined in counter-clockwise order.
Determine if the ray is parallel to the triangle: Check if the ray's direction vector is nearly
		parallel (within a small epsilon value) to the triangle's normal vector.
		If they are nearly parallel, it means the ray and triangle are unlikely to intersect,
		and the algorithm can return false.
Compute the determinant and check for backface culling: Calculate the determinant of the ray direction
		 vector and one of the triangle's edges. If the determinant is negative,
		 it means the ray is pointing away from the triangle's front face,
		 and backface culling can be applied. If backface culling is enabled,
		 the algorithm can return false.
Calculate the intersection point: Compute the vector from the ray's origin to one of the triangle's
		vertices (often called the "edge 1" vector). Compute the dot product of this vector
		with the cross product of the ray direction and the triangle's edge 2 vector.
		This value is used to calculate the barycentric coordinate of the intersection point along
		the ray direction.
Check the barycentric coordinates: After obtaining the barycentric coordinate,
	check if it falls within the valid range of [0, 1]. If it is outside this range,
	it means the intersection point lies outside the triangle, and the algorithm can return false.
Compute the other barycentric coordinates: Using the barycentric coordinate obtained in the previous
	step, compute the remaining two barycentric coordinates.
	These coordinates represent the weights needed to interpolate values across the triangle.
Check for ray-plane intersection: Verify if the ray-plane intersection occurs within the triangle.
	This is done by checking if the sum of the barycentric coordinates is less than or equal to 1.
	If it is greater than 1, it means the intersection point lies outside the triangle,
	and the algorithm can return false.
Output: If all the checks pass, the algorithm can return true, indicating that the ray intersects
	the triangle.
	Additionally, it can compute the intersection point by interpolating the values of the triangle's
	vertices using the barycentric coordinates.
*/


/* basic C++ structure for triangles
bool rayTriangleIntersect(
	const Vec3f &orig, const Vec3f &dir,
	const Vec3f &v0, const Vec3f &v1, const Vec3f &v2,
	float &t, float &u, float &v)
{
#ifdef MOLLER_TRUMBORE
	Vec3f v0v1 = v1 - v0;
	Vec3f v0v2 = v2 - v0;
	Vec3f pvec = dir.crossProduct(v0v2);
	float det = v0v1.dotProduct(pvec);
#ifdef CULLING
	// if the determinant is negative, the triangle is 'back facing'
	// if the determinant is close to 0, the ray misses the triangle
	if (det < kEpsilon) return false;
#else
	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < kEpsilon) return false;
#endif
	float invDet = 1 / det;

	Vec3f tvec = orig - v0;
	u = tvec.dotProduct(pvec) * invDet;
	if (u < 0 || u > 1) return false;

	Vec3f qvec = tvec.crossProduct(v0v1);
	v = dir.dotProduct(qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = v0v2.dotProduct(qvec) * invDet;

	return true;
#else
	...
#endif
}*/

/* A 0.5 200,200,200
C 0.0,0.0,0.0 0,0.0,1 90
L -10.0,5.0,-4.0 0.9 255,255,255
tr 0,2,0 0,2,0 255,255,0*/

double  dist_triangle(const t_ray *ray, const t_obj *obj)
{
	double	det;
	double	inv_det;
	t_vec3	pvec;
	t_vec3	tvec;
	t_vec3	qvec;
	double	bar_weights[2];


	// Define the vertices of the triangle
	t_vec3 p0 = {1.0, 0.0, -0.5};
	t_vec3 p1 = {0.0, -4.5, -0.5};
	t_vec3 p2 = {0.5, 0.0, -0.5};

	// Calculate the vectors v0v1 and v0v2
	t_vec3 v0v1 = vec3_sub(obj->tri_point[1], obj->tri_point[0]); //{p1.x - p0.x, p1.y - p0.y, p1.z - p0.z};
	t_vec3 v0v2 = vec3_sub(obj->tri_point[2], obj->tri_point[0]); //{p2.x - p0.x, p2.y - p0.y, p2.z - p0.z};

	// Calculate the cross product of ray direction and v0v2
	pvec = vec3_cross(ray->direction, v0v2);

	// Calculate the determinant
	det = vec3_dot(v0v1, pvec);

	// Check if the ray and triangle are parallel (determinant close to 0)
	if (fabs(det) < EPSILON)
		return (DBL_MAX);

	// Calculate the inverse determinant
	inv_det = -1.0 / det;

	// Calculate the vector tvec
	tvec = vec3_sub(ray->origin, p0); //{ray->origin.x - p0.x, ray->origin.y - p0.y, ray->origin.z - p0.z};

	// Calculate the parameter u
	bar_weights[U] = vec3_dot(tvec, pvec) * inv_det;

	// Check if u is within the valid range
	if (bar_weights[U] < 0.0 || bar_weights[U] > 1.0)
		return (DBL_MAX);

	// Calculate the vector qvec -qvec is a common choice in the Möller-Trumbore algorithm to represent the calculated vector
	qvec = vec3_cross(tvec, v0v1);

	// In the Möller-Trumbore algorithm, after calculating the parameter u, which represents the intersection point's
	// barycentric coordinate relative to the triangle's first edge, the parameter v is calculated to determine the intersection point's
	// barycentric coordinate relative to the triangle's second edge.
	// If v is less than 0 or u + v is greater than 1, it indicates that the intersection point is outside the triangle,
	// and the function returns 0.0, indicating no intersection. Otherwise,
	// if the conditions are satisfied, v represents the intersection point's barycentric coordinate relative to the triangle's second edge.
	// In summary, v is a parameter used in the algorithm to determine if the intersection point lies within the triangle or not.

	// Calculate the parameter v
	bar_weights[V] = vec3_dot(ray->direction, qvec) * inv_det;

	// Check if v is within the valid range
	if (bar_weights[V] < 0.0 || bar_weights[U] + bar_weights[V] < 1.0)
		return (DBL_MAX);

	// Calculate the intersection distance along the ray
	return (vec3_dot(v0v2, qvec) * inv_det);
}
