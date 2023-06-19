/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:21:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/19 18:24:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_skip_ws(char **line)
{
	while (**line == ' ')
		*line += 1;
}

void	ft_skip_num(char **line, int mode)
{
	int flag;

	flag = 0;
	while (ft_isdigit(**line) || (mode != INT && **line == '.' && !flag))
	{
		if (**line == '.')
			flag++;
		*line += 1;
	}
	if (ft_isspace(**line))
		return ;
	ft_error(num_err);
}

int32_t	get_colour(char **line)
{
	int	colour[4];
	int	res;
	int	i;

	i = 1;
	while (i < 4)
	{
		ft_skip_ws(line);
		colour[i] = ft_atoi(*line);
		ft_skip_num(line, INT);
		if (colour[i] < 0 || colour[i] > 255)
			ft_error(range_err);
		if (*(*line + 1) != ',' && i < 3)
			ft_error(num_err);
		*line += 2;
	}
	return (create_trgb(0xFF, colour[1], colour[2], colour[3]));
}

double	get_double(char **line, int mode)
{
	double	res;

	res = ft_atof(*line);
	ft_skip_num(line, REAL);
	if (mode == RATIO && 0 <= res && res <= 1)
		return (res);
	if (mode == REAL)
		return (res);
	if (mode == BALANCE && -1 <= res && res <= 1)
		return (res);
	if (mode == ANGLE && 0 <= res && res <= 180)
		return (res);
	ft_error(num_err);
}

t_vec3	get_vec3(char **line)
{
	t_vec3	vec;
	int		i;

	i = 0;
	ft_skip_ws(line);
	vec.x = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	vec.y = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	vec.z = ft_atof(*line);
	ft_skip_num(line, REAL);
	return (vec);
}