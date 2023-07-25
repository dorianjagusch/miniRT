/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:30:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/25 15:34:36 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>

void	ft_error(int error)
{
	static const	char	(*errors[]) = {
		"File extension must be .rt\n",
		"Input format invalid. Consult the subject for format specifications.\n",
		"Numerical value out of range\n",
		"Identifier not recognised.\n",
		"Scene must have only one camera, ambient light and one point light.\n",
		"Scene must have at least one camera.\n",
		"Error opening .obj file.\n",
		"Error opening .xpm file.\n"
	};

	ft_printf_fd(STDERR_FILENO, "\e[2;31mError\x1b[m:\n");
	if (error < 160)
		ft_printf_fd(STDERR_FILENO, "%s\n", strerror(error));
	else
		ft_printf_fd(STDERR_FILENO, "%s\n", errors[error - 160]);
	exit(error);
}

void	check_line(char **line)
{
	ft_skip_ws(line);
	ft_skip_num(line, INT, 0);
	ft_skip_ws(line);
	if (**line != '\n')
		ft_error(num_err);
}

void	validate_scene(t_scene *scene)
{
	int	num;

	num = 0;
	while (num < scene->n_lights && scene->lights[num].valid)
	{
		if (scene->n_lights != 1)
			ft_error(content_err);
		num++;
	}
	if (scene->cam.valid != 1)
		ft_error(content_err);
	if (scene->amb.valid != 1)
		ft_error(content_err);
}
