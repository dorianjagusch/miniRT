/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_setup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:49:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 17:31:09 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_bonus.h"
#include "errors_bonus.h"
#include "minirt_bonus.h"

void	get_texture_dim(char **file, int *width, int *height)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		i;

	fd = open(*file, O_RDONLY);
	i = 0;
	line = get_next_line(fd, FALSE);
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
		line = get_next_line(fd, FALSE);
	}
	close (fd);
	get_next_line(fd, TRUE);
}

static void	get_texels(void *mlx, t_picture *texture)
{
	get_texture_dim(&(texture->file), &(texture->width),
		&(texture->height));
	if (!texture->width || !texture->height)
		ft_error(xpm_err);
	texture->texels = mlx_xpm_file_to_image(mlx, texture->file,
			&(texture->width),
			&(texture->height));
	if (!(texture->texels))
		ft_error(xpm_err);
	texture->addr = mlx_get_data_addr(texture->texels, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

void	set_picture(t_img *img, t_texture **texture, t_vec4 *col, char *line)
{
	char	*tmp;

	tmp = ft_strnstr(line, "-texture", 200);
	if (!tmp)
		return ;
	*texture = ft_calloc(1, sizeof(t_texture));
	if (!*texture)
		ft_error(ENOMEM);
	(*texture)->file = ft_get_word(tmp + 9);
	if (!(*texture)->file)
		ft_error(ENOMEM);
	if (!ft_strncmp((*texture)->file, "checkers", 8))
	{
		(*texture)->proc_pat = set_board(10, 10, *col,
				vec4_multf(*col, 0.5));
		(*texture)->pattern = checkers_pat;
	}
	else if (!ft_strncmp((*texture)->file, "brick", 5))
		(*texture)->pattern = brick_pat;
	else if ((*texture)->file)
	{
		get_texels(img->win.mlx, &(*texture)->picture);
		(*texture)->pattern = texture_pat;
	}
}

void	set_normals(t_img *img, t_texture **texture, char *line)
{
	char	*tmp;

	tmp = ft_strnstr(line, "-normal", 200);
	if (!tmp)
		return ;
	*texture = ft_calloc(1, sizeof(t_texture));
	if (!*texture)
		ft_error(ENOMEM);
	(*texture)->file = ft_strdup(tmp + 9);
	if ((*texture)->file)
	{
		get_texels(img->win.mlx, &(*texture)->picture);
		(*texture)->pattern = texture_pat;
	}
}
