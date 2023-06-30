/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:30:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/25 23:16:01 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(int error)
{
	static const	char	(*errors[]) = {
		"File extension must be .rt.\n",
		"Input format invalid. Consult the subject for format specifications.\n",
		"Numerical value out of range\n",
		"Identifier not recognised.\n",
		"Scene must have only one Camera, Ambient light and  at least one light.\n",
	};

	if (error < 160)
		ft_printf_fd(STDERR_FILENO, "%s\n", strerror(error));
	else
		ft_printf_fd(STDERR_FILENO, "%s\n", errors[error - 160]);
	exit(error);
}

void	validate_scene(t_scene *scene)
{
	if (scene->light.valid != 1)
		ft_error(content_err);
	if (scene->cam.valid != 1)
		ft_error(content_err);
	if (scene->amb.valid != 1)
		ft_error(content_err);
}