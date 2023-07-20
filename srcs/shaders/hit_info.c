/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 07:32:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/20 13:21:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "materials.h"
#include "objects.h"
#include "shaders.h"

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
	else
		return (obj->mesh.colour);
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
	else
		return (obj->mesh.material);
}

void	set_hitpoint(t_scene *scene, t_ray *ray, t_hitresult *hit)
{
	int	triangle_id;

	hit->position = vec3_add(ray->origin,
			vec3_multf(ray->direction, hit->distance));
	hit->point2cam = vec3_sub(hit->position, ray->origin);
	vec3_normalize(&hit->point2cam);
	hit->colour = get_texture_colour(&(scene->objs[hit->obj_id]),
			&(hit->position));
	hit->normal = get_normal(&(scene->objs[hit->obj_id]), hit->position);
	hit->position = vec3_add(hit->position,
			vec3_multf(vec3_multf(hit->normal, 10e-3),
				-ft_sign(vec3_dot(hit->normal, scene->cam.dir))));
	if (scene->objs[hit->obj_id].type == mesh_obj)
	{
		triangle_id = scene->objs[hit->obj_id].mesh.obj_id;
		hit->normal = scene->objs[hit->obj_id].mesh.triangle_data[triangle_id].triangle.normal;
		//hit->material = get_hitmaterial(&(scene->objs[hit->obj_id].mesh.obj_id));
		hit->colour = scene->objs[hit->obj_id].mesh.triangle_data[triangle_id].triangle.colour;
		return ;
	}
	hit->material = get_hitmaterial(&(scene->objs[hit->obj_id]));
	//get_hitcolour(&(scene->objs[hit->obj_id]));
	hit->type = scene->objs->type;
}