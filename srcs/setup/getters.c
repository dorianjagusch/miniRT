/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:21:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 14:50:41 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_skip_ws(char **line)
{
	ft_printf("in WS\n");
	while (**line == ' ')
		*line += 1;
	ft_printf("out WS\n");
}

void	ft_skip_num(char **line, int mode)
{
	int	flag;

	flag = 0;
	while ((ft_isdigit(**line) || (mode != INT && **line == '.' && !flag)) && **line != '\0')
	{
		if (**line == '.')
			flag++;
		*line += 1;
	}
	if (ft_isspace(**line) || **line == ',')
	{
		ft_printf("Number skip success\n");
		return ;
	}
	ft_error(num_err);
}

t_vec4	get_colour(char **line)
{
	int		colour[4];
	t_vec4	res;
	int		i;

	i = 1;
	ft_printf("In get colour %s\n", *line);
	while (i < 4)
	{
		ft_skip_ws(line);
		colour[i] = ft_atoi(*line);
		ft_printf("got int %d\n", i);
		if (colour[i] < 0 || colour[i] > 255)
			ft_error(range_err);
		ft_printf("colour scan on %c\n", *(*line + 1));
		if ((*(*line + 1) != ',') && i < 3)
			ft_error(num_err);
		i++;
		*line += 2;
	}
	res = ft_trgbtov4(colour);
	ft_rgbtonorm(&res);
	return (res);
}

double	get_double(char **line, int mode)
{
	double	res;

	res = ft_atof(*line);
	ft_skip_num(line, REAL);
	if (mode == RATIO && 0 <= res && res <= 1)
	{
		ft_printf("res: %f, left: %s", res, *line);
		return (res);
	}
	else if (mode == REAL)
	{
		ft_printf("res: %f, left: %s", res, *line);
		return (res);
	}
	else if (mode == BALANCE && -1 <= res && res <= 1)
	{
		ft_printf("res: %f, left: %s", res, *line);
		return (res);
	}
	else if (mode == ANGLE && 0 <= res && res <= 180)
	{
		ft_printf("res: %f, left: %s", res, *line);
		return (res);
	}
	else
		ft_error(num_err);
	return (DBL_MAX);
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
