/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:21:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/07 17:00:56 by smorphet         ###   ########.fr       */
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
	int	flag;

	flag = 0;
	
	if(**line == '-' || **line == '+')
		*line += 1;
	while ((ft_isdigit(**line) || (mode != INT && **line == '.' && !flag)) && **line != '\0') 
	{
		if (**line == '.')
			flag++;
		*line += 1;
	}
	if (ft_isspace(**line) || **line == ',')
		return ;
	ft_error(num_err);
}

t_vec4	get_colour(char **line)
{
	int		colour[4];
	t_vec4	res;
	int		i;

	colour[0] = 1;
	i = 1;
	while (i <= 3)
	{
		ft_skip_ws(line);
		colour[i] = ft_atoi(*line);
		if (colour[i] < 0 || colour[i] > 255)
			ft_error(range_err);
		if (i == 3)
			break;
        while (**line != ',' || **line == '\n' || **line == '\0')
            (*line)++;
		if ((**line != ',') && i < 3)
			ft_error(num_err);
		i++;
		*line += 1;
	}
	res = ft_trgbtov4(colour);
	ft_rgbtonorm(&res);
	return (res);
}

float	get_float(char **line, int mode)
{
	float	res;

	res = 0;
	res = ft_atof(*line);
	ft_skip_num(line, REAL);
	if (mode == RATIO && 0 <= res && res <= 1)
		return (res);
	else if (mode == REAL)
		return (res);
	else if (mode == BALANCE && -1 <= res && res <= 1)
		return (res);
	else if (mode == ANGLE && 0 <= res && res <= 180)
		return (res);
	else
		ft_error(num_err);
	return (FLT_MAX);
}

t_vec3	get_vec3(char **line)
{
	t_vec3	vec;

	ft_skip_ws(line);
	vec.x = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	if (**line == ',') 
		*line += 1;
	vec.y = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	if (**line == ',')
		*line += 1; 
	vec.z = ft_atof(*line);
	if (**line == '-')
		*line += 1;
	ft_skip_num(line, REAL);
	return (vec);
}
