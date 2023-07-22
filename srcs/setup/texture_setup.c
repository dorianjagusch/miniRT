/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:49:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/22 18:38:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"
#include "errors.h"
#include "minirt.h"

void	get_texture_dim(char **file, int *width, int *height)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		i;

	fd = open(*file, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line && i < 4)
	{
		if (!ft_strncmp(line, "\"", 1))
		{
			tmp = line + 1;
			*width = ft_atoi(tmp);
			ft_skip_num(&tmp, INT, FALSE);
			*height = ft_atoi(tmp);
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}

void	get_texels(t_picture *texture)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		ft_error(ENOMEM);
	get_texture_dim(&(texture->file), &(texture->width),
		&(texture->height));
	printf("Dims: width: %d, height %d\n", texture->width, texture->height);
	if (!texture->width || texture->height)
		ft_error(xpm_err);
	texture->texels = mlx_xpm_file_to_image(mlx_ptr, texture->file,
			&(texture->width),
			&(texture->height));
	if (!(texture->texels))
		ft_error(xpm_err);
}

void	set_picture(t_texture *texture, t_vec4 *col, char *line)
{
	char	*tmp;

	tmp = ft_strnstr(line, "-texture", 200);
	if (!tmp)
		return ;
	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
		ft_error(ENOMEM);
	texture->file = ft_strdup(tmp + 9);
	if (!texture->file)
		ft_error(ENOMEM);
	ft_skip_ws(&(texture->file));
	if (!ft_strncmp(texture->file, "\"checkers\"", 8))
	{
		texture->proc_pat = set_board(10, 10, *col,
				vec4_multf(*col, 0.5));
		texture->pattern = checkers_pat;
	}
	else if (!ft_strncmp(texture->file + 1, "\"brick\"", 5))
		texture->pattern = brick_pat;
	else if (texture->file)
	{
		get_texels(&texture->picture);
		texture->pattern = texture_pat;
	}
}

void	set_normals(t_texture *texture, t_vec4 *col, char *line)
{
	char	*tmp;

	tmp = ft_strnstr(line, "-normal", 200);
	if (!tmp)
		return ;
	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
		ft_error(ENOMEM);
	texture->file = ft_strdup(tmp + 9);
	if (texture->file)
	{
		get_texels(&texture->picture);
		texture->pattern = texture_pat;
	}
}
