/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:53:02 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/18 09:10:51 by djagusch         ###   ########.fr       */
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
	t_vec3	transl_point;
	t_vec2	uv;

	transl_point = vec3_sub(*point, obj->sphere.pos);
	angle = atan2f(transl_point.x, transl_point.z);
	polar_angle = acosf(transl_point.y / obj->sphere.radius);
	uv.x = angle * M_1_DIV_2PI;
	uv.x = 1 - (uv.x + 0.5);
	uv.y = 1 - polar_angle * M_1_DIV_PI;
	return (uv);
}
