/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:53:02 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/17 16:21:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"
#include <math.h>
#include "patterns.h"


// t_vec2 spherical_map(t_vec3 point, t_sphere *sphere)
// {
//     t_vec2 uv;

//     // Translate the point relative to the sphere's position
//     t_vec3 translated_point = point - sphere->position;

//     // Compute spherical coordinates
//     float angle = atan2f(translated_point.x, translated_point.z);
//     float polar_angle = acosf(translated_point.y / sphere->radius);

//     // Map to UV coordinates
//     uv.x = angle / (2.0 * M_PI);
//     uv.x = 1.0 - (uv.x + 0.5);
//     uv.y = 1.0 - (polar_angle / M_PI);

//     return uv;
// }

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
