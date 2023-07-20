/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:04:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/20 12:00:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "minirt.h"

int	is_obj(char *line)
{
	ft_skip_ws(&line);
	if (ft_strncmp(line, "sp", 2) == 0
		|| ft_strncmp(line, "pl", 2) == 0
		|| ft_strncmp(line, "cy", 2) == 0
		|| ft_strncmp(line, "di", 2) == 0
		|| ft_strncmp(line, "tr", 2) == 0)
		return (1);
	return (0);
}
