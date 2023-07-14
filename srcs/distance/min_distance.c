/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:55:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/14 07:58:30 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shaders.h"
#include "float.h"

float	dist_mesh(const t_ray *ray, t_object *obj)
{
	int		j;
	float	new_dist;
	float	hit_dist;

	j = 0;
	new_dist = 0;
	hit_dist = FLT_MAX;
	while (j < obj->mesh.n_triangles)
	{
		new_dist = dist_triangle(ray, &obj->mesh.triangle_data[j]);
		if (new_dist < hit_dist)
		{
			obj->mesh.obj_id = j;
			hit_dist = new_dist;
		}
		j++;
	}
	return (hit_dist);
}

float	get_dist(const t_ray *ray, t_object *obj)
{
	static const t_dist_function	func[] = {
		dist_sphere,
		dist_plane,
		dist_cylinder,
		dist_disk,
		dist_triangle,
		dist_box,
		dist_mesh
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
	else //(obj->type == mesh_obj)
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
	else // (obj->type == mesh_obj)
		return (obj->mesh.material);
}

void	set_hitpoint(t_scene *scene, t_ray *ray, t_hitresult *hit)
{
	int	triangle_id;

	hit->position = vec3_add(ray->origin,
			vec3_multf(ray->direction, hit->distance));
	hit->point2cam = vec3_sub(hit->position, ray->origin);
	vec3_normalize(&hit->point2cam);
	hit->normal = get_normal(&(scene->objs[hit->obj_id]), hit->position);
	hit->position = vec3_add(hit->position,
	vec3_multf(hit->normal, 10e-2));
	if (scene->objs[hit->obj_id].type == mesh_obj)
	{
		triangle_id = scene->objs[hit->obj_id].mesh.obj_id;
		hit->normal = scene->objs[hit->obj_id].mesh.triangle_data[triangle_id].triangle.normal;
		//hit->material = get_hitmaterial(&(scene->objs[hit->obj_id].mesh.obj_id));
		hit->colour = scene->objs[hit->obj_id].mesh.triangle_data[triangle_id].triangle.colour;
		return ;
	}
	hit->material = get_hitmaterial(&(scene->objs[hit->obj_id]));
	hit->colour = get_hitcolour(&(scene->objs[hit->obj_id]));
	hit->type = scene->objs->type;
}

void	get_closest(const t_scene *scene, const t_ray *ray, t_hitresult *hit)
{
	int			i;
	float		new_dist;

	i = 0;
	new_dist = 0;
	hit->distance = FLT_MAX;
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
