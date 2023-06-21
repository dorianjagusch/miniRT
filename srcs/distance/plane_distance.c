/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:48:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/21 22:17:30 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

double	dist_plane(t_ray *ray, t_obj *obj)
{
	double	p_dist;

	p_dist = ft_v3dot(ft_v3sub(obj->position, ray->origin), obj->normal);
	p_dist /= ft_v3dot(ray->direction, obj->normal);
	if (p_dist > 0)
		return (p_dist);
	return (DBL_MIN);
}