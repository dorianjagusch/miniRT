/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 09:57:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"
#include "float.h"

double	get_dist(const t_ray *ray, const t_object *obj)
{
	static const t_dist_function	func[] = {
		dist_sphere,
		dist_plane,
		dist_cylinder,
		dist_disk,
		dist_triangle,
		dist_box,
	};

	return (func[obj->type](ray, obj));
}


t_vec4	get_hitcolour(const t_object *obj)
{
	if (obj->type == sphere_obj)
		return (obj->sphere.colour);
	else if (obj->type == plane_obj)
		return (obj->plane.colour);
	else if (obj->type == cylinder_obj)
		return (obj->cylinder.colour);
	else if (obj->type == disk_obj)
		return (obj->disk.colour);
	else if (obj->type == triangle_obj)
		return (obj->triangle.colour);
	else if (obj->type == box_obj)
		return (obj->box.colour);
}

t_material_e	get_hitmaterial(const t_object *obj)
{
	if (obj->type == sphere_obj)
		return (obj->sphere.material);
	else if (obj->type == plane_obj)
		return (obj->plane.material);
	else if (obj->type == cylinder_obj)
		return (obj->cylinder.material);
	else if (obj->type == disk_obj)
		return (obj->disk.material);
	else if (obj->type == triangle_obj)
		return (obj->triangle.material);
	else if (obj->type == box_obj)
		return (obj->box.material);
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
	hit->material = get_hitmaterial(&(scene->objs[hit->obj_id]));
	hit->colour = get_hitcolour(&(scene->objs[hit->obj_id]));
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


