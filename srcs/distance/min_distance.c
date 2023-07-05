/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 19:24:33 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"
#include "float.h"

double	get_dist(const t_ray *ray, const t_obj *obj)
{
	static const t_dist_func	func[] = {
	{sphere, &dist_sphere},
	{plane, &dist_plane},
	{cylinder, &dist_cylinder},
	{disk, &dist_disk},
	{triangle, &dist_triangle}
	};

	return (func[obj->type].dist_funct(ray, obj));
}

void	set_hitpoint(t_scene *scene, t_ray *ray, t_hitresult *hit)
{
	assert(!vec3_isnan(ray->origin));
	assert(!vec3_isnan(ray->direction));
	assert(!isnan(hit->distance));

	hit->position = vec3_add(ray->origin,
	vec3_multf(ray->direction, hit->distance));
	DEBUG_ONLY(printf("setting of hit point"));
	DEBUG_ONLY(print_vec3(hit->position, "set hit point"));
	assert(!vec3_isnan(hit->position));

	hit->point2cam = vec3_sub(hit->position, ray->origin);
	vec3_normalize(&hit->point2cam);
	assert(!vec3_isnan(hit->position));
	hit->normal = get_normal(&(scene->objs[hit->obj_id]), hit->position);
	assert(!vec3_isnan(hit->normal));
	hit->position = vec3_add(hit->position,
			vec3_multf(hit->normal, 1.0E-04));
}

void	get_closest(const t_scene *scene, const t_ray *ray, t_hitresult *hit)
{
	int			i;
	double		new_dist;

	i = 0;
	hit->distance = DBL_MAX;
	while (scene->objs && i < scene->n_objs)
	{
		new_dist = get_dist(ray, &(scene->objs[i]));
		if (new_dist < hit->distance)
		{
			hit->obj_id = i;
			hit->distance = new_dist;
		}
		i++;
	}
}


