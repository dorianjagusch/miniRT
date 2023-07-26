/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 14:16:13 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <stdio.h>


// void print_texture_file_contents(const t_texture *texture)
// {
//     if (texture->file != NULL) {
//         printf("Texture file contents: %s\n", texture->file);
//     } else {
//         printf("Texture file is empty or not initialized.\n");
//     }
// }

void	free_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->n_objs)
	{
		// print_texture_file_contents(&scene->objs[i].meta.tex_col);
		if (scene->objs[i].type == cylinder_obj)
		{
			free(scene->objs[i].cylinder.top);
			free(scene->objs[i].cylinder.bottom);
		}
		if (scene->objs[i].type == cone_obj)
			free(scene->objs[i].cone.bottom);
		free(scene->objs[i].meta.tex_col);
    	free(scene->objs[i].meta.tex_norm);
		i++;
	}
	if (scene->objs)
		free(scene->objs);
	if (scene->lights)
		free(scene->lights);
	if (scene->specular)
		free(scene->specular);
	if (scene->distances)
		free(scene->distances);
	if (scene->directions)
		free(scene->directions);
}

void	free_arrays(t_mesh *mesh)
{
	int	count;

	if (mesh->normals)
		free(mesh->normals);
	if (mesh->vertex)
		free(mesh->vertex);
	if (mesh->textures)
		free(mesh->textures);
	if (mesh->faces)
	{
		count = 0;
		while (count < mesh->count_f)
		{
			free(mesh->faces[count]);
			count++;
		}
	}
}

void	free_img(t_img *img)
{
	if (img->img)
		mlx_destroy_image(img->win.mlx, img->img);
	if (img->win.win)
		mlx_destroy_window(img->win.mlx, img->win.win);
	if (img->scene->objs)
		free_scene(img->scene);
}
