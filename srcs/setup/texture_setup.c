/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:49:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/22 14:15:19 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"
#include "errors.h"
#include "minirt.h"

void	get_png(t_texture *texture)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		ft_error(ENOMEM);
	}
	texture->picture.picture = mlx_xpm_file_to_image(mlx_ptr, texture->file,
			&(texture->picture.width),
			&(texture->picture.height));
	if (!(texture->picture.picture))
		ft_error(png_err);
	texture->picture.normal = mlx_xpm_file_to_image(mlx_ptr, texture->file,
			&(texture->picture.width),
			&(texture->picture.height));
	if (!(texture->picture.normal))
		ft_error(png_err);
}

void	set_meta(t_object *object, char *line)
{
	object->meta.texture = ft_calloc(1, sizeof(t_texture));
	if (!object->meta.texture)
		ft_error(ENOMEM);
	object->meta.texture->file = ft_strnstr(line, "-texture", 200);
	if (!object->meta.texture->file)
		return ;
	object->meta.texture->file += 9;
	ft_skip_ws(&(object->meta.texture->file));
	if (!ft_strncmp(object->meta.texture->file, "checkers", 8))
	{
		object->meta.texture->proc_pat = set_board(10, 10, object->meta.colour,
				vec4_multf(object->meta.colour, 0.5));
		object->meta.texture->pattern = checkers_pat;
	}
	else if (!ft_strncmp(object->meta.texture->file, "brick", 5))
		object->meta.texture->pattern = brick_pat;
	else if (object->meta.texture->file)
		get_png(object->meta.texture);
}
