#include <stdio.h>
#include <math.h>
#include <float.h>
#include "vector_math.h"
#include "scene.h"
#include "shaders.h"

double	dist_plane(t_ray *ray, t_obj *plane)
{
	double	denominator;
	t_vec3	oc;
	double	distance;

	denominator = vec3_dot(plane->normal, ray->direction);
	if (fabs(denominator) < 0.000001)
		return (DBL_MAX);
	distance = vec3_dot(vec3_sub(plane->position, ray->origin),
			plane->normal) / denominator;
	if (distance < 0)
		return (DBL_MAX);
	return (distance);
}
