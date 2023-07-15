/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:53:02 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/15 16:04:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"
#include <math.h>
#include "patterns.h"

t_vec2	spherical_map(t_vec3 *point, t_object *obj)
{
	float	angle;
	float	polar_angle;
	t_vec2	uv;

	angle = atan2f(point->x, point->z);
	polar_angle = acosf(point->y / obj->sphere.radius);
	uv.x = angle * M_1_DIV_2PI;
	uv.x = 1 - (uv.x + 0.5);
	uv.y = 1 - polar_angle * M_1_DIV_PI;
	return (uv);
}
