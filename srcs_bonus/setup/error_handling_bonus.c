/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:30:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/26 17:09:43 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	ft_error(int error)
{
	static const	char	(*errors[]) = {
		"File extension must be .rt\n",
		"Input format invalid. Consult the subject for format specifications.\n",
		"Numerical value out of range\n",
		"Identifier not recognised.\n",
		"Scene must have at leat one camera.\n",
		"Scene must have only one camera, ambient light and at least one \
		point light.\n",
		"Error opening .obj file.\n",
		"Error opening .xpm file.\n",
		"Line exceeds 255 characters\n"
	};

	ft_printf_fd(STDERR_FILENO, "\e[2;31mError\x1b[m:\n");
	if (error < 160)
		ft_printf_fd(STDERR_FILENO, "%s", strerror(error));
	else
		ft_printf_fd(STDERR_FILENO, "%s", errors[error - 160]);
	exit(error);
}

void	validate_scene(t_scene *scene)
{
	int	num;

	num = 0;
	while (num < scene->n_lights && scene->lights[num].valid)
	{
		if (scene->lights[num].valid != 1)
			ft_error(content_err);
		num++;
	}
	if (scene->cam.valid != 1)
		ft_error(content_err);
	if (scene->amb.valid != 1)
		ft_error(content_err);
}
