/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:53:02 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/13 19:23:01 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_vec2	spherical_map(t_vec3 point, t_sphere *sphere)
{
	float	angle;
	float	polar_angle;
	t_vec2	uv;

	angle = atan2f(point.x, point.z);
	polar_angle = acosf(point.y / sphere->radius);
	uv.x = angle / (2 * M_PI);
	uv.x = 1 - (uv.x + 0.5);
	uv.y = 1 - polar_angle / M_PI;
	return (uv);
}
