/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:42:44 by smorphet          #+#    #+#             */
/*   Updated: 2023/07/05 14:32:03 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

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

// w1 = Ax(Cy - Ay) + (Py - Ay) *?(Cx-Ax)- Px(Cy -Ay)
//		/ (By - Ay)(cX - Ax) - (Bx - Ax)(Cy - Ay)

// w2 = Py - Ay -W1(By - Ay)
//		/ Cy - Ay 

double dist_triangle(t_ray *ray, t_obj *obj) // TODO: dont have capitals in variables, and these should all be const
{
		double p_dist;
		t_vec2 A;
		t_vec2 B;
		t_vec2 C;
		t_vec3 p_hit;
		double w1;
		double w2 = 0;

		A.x = 0.1;
		A.y = -9.0;
		B.x = 2.0;
		B.y = -7.0;
		C.x = 4.0;
		C.y = -9.0;


		p_dist = dist_plane(ray, obj);

		if (p_dist == DBL_MAX)
			return (DBL_MAX);
			
		assert(!vec3_isnan(ray->origin));
		assert(!vec3_isnan(ray->direction));
		assert(!isnan(p_dist));
		
		p_hit.z = 1;
		p_hit = vec3_add(ray->origin, vec3_multf(ray->direction, p_dist));
		
		DEBUG_ONLY(printf("inside the dist triangle function\n"));

		assert(!vec3_isnan(p_hit));
		
		w1 = (A.x * (C.y - A.y) + (p_hit.y - A.y) * (C.x - A.x) - p_hit.x * (C.y - A.y)) / ((B.y - A.y) * (C.x - A.x) - (B.x - A.x) * (C.y - A.y));
		printf(" w1  = %f\n", w1);

		if (fabs(C.y - A.y) < EPSILON)
	    	w2 = -4.0; // Set a default value or handle it appropriately
		else
	    	w2 = (p_hit.y - A.y - w1 * (B.y - A.y)) / (C.y - A.y);

		printf("w1 = %f	w2 = %f\n", w1, w2);
		double result = w1 + w2;

		if (result >= 0 && result <= 1 )
			return(p_dist);
	    return (DBL_MAX);
	}


/*
bool rayTriangleIntersect(
    const Vec3f &orig, const Vec3f &dir,
    const Vec3f &v0, const Vec3f &v1, const Vec3f &v2,
    float &t)
{
    // compute the plane's normal
    Vec3f v0v1 = subtract(v1, v0);
    Vec3f v0v2 = subtract(v2, v0);
    // no need to normalize
    Vec3f N = crossProduct(v0v1, v0v2); // N
    float area2 = length(N);
 
    // Step 1: finding P
    
    // check if the ray and plane are parallel.
    float NdotRayDirection = dotProduct(N, dir);
    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
        return false; // they are parallel, so they don't intersect! 

    // compute d parameter using equation 2
    float d = -dotProduct(N, v0);
    
    // compute t (equation 3)
    t = -(dotProduct(N, orig) + d) / NdotRayDirection;
    
    // check if the triangle is behind the ray
    if (t < 0) return false; // the triangle is behind
 
    // compute the intersection point using equation 1
    Vec3f P = { orig.x + t * dir.x, orig.y + t * dir.y, orig.z + t * dir.z };
 
    // Step 2: inside-outside test
    Vec3f C; // vector perpendicular to triangle's plane
 
    // edge 0
    Vec3f edge0 = subtract(v1, v0);
    Vec3f vp0 = subtract(P, v0);
    C = crossProduct(edge0, vp0);
    if (dotProduct(N, C) < 0) return false; // P is on the right side
 
    // edge 1
    Vec3f edge1 = subtract(v2, v1);
    Vec3f vp1 = subtract(P, v1);
    C = crossProduct(edge1, vp1);
    if (dotProduct(N, C) < 0)  return false; // P is on the right side
 
    // edge 2
    Vec3f edge2 = subtract(v0, v2);
    Vec3f vp2 = subtract(P, v2);
    C = crossProduct(edge2, vp2);
    if (dotProduct(N, C) < 0) return false; // P is on the right side;

    return true; // this ray hits the triangle
}
*/