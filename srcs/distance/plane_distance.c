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
	double	t;

	denominator = vec3_dot(plane->normal, ray->direction);
	if (fabs(denominator) < 0.000001)
		return (DBL_MAX);
	oc = vec3_sub(plane->position, ray->origin);
	t = vec3_dot(oc, plane->normal) / denominator;
	if (t < 0)
		return (DBL_MAX);
	return (t);
}
