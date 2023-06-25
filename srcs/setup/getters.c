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
	//ft_printf("in WS\n");
	while (**line == ' ')
		*line += 1;
	//ft_printf("out WS\n");
}

void	ft_skip_num(char **line, int mode)
{
	int	flag;

	flag = 0;
	while ((ft_isdigit(**line) || **line == '-' || (mode != INT && **line == '.' && !flag)) && **line != '\0') 
	{
		if (**line == '.')
			flag++;
		*line += 1;
	}
	if (ft_isspace(**line) || **line == ',') //added '-' might potentiall cause issues
	{
		ft_printf("Number skip success\n");
		ft_printf("line at return of skip num: |%s|\n", *line);
		return ;
	}
	ft_error(num_err);
}

t_vec4	get_colour(char **line)
{
	int		colour[4];
	t_vec4	res;
	int		i;

	colour[0] = 0; //potentially causing issues?
	i = 1;
	while (i < 4)  // why is this 4? ive changed it to 3 for testing
	{
		ft_skip_ws(line);
		colour[i] = ft_atoi(*line);
		if (colour[i] < 0 || colour[i] > 255)
			ft_error(range_err);
        while (**line != ',' || **line == '\n') //  && !ft_isspace(**line)  we need to move passed the numbers already used
            (*line)++;
		if ((**line != ',') && i < 3) //unsure what this is checking?
			ft_error(num_err);
		i++;
		*line += 1;
	}
	ft_printf("colour 0 = %d\n", colour[0]);
	ft_printf("colour 1 = %d\n", colour[1]);
	ft_printf("colour 2 = %d\n", colour[2]);
	ft_printf("colour 3 = %d\n", colour[3]);
	res = ft_trgbtov4(colour);
	ft_rgbtonorm(&res);
	return (res);
}

double	get_double(char **line, int mode)
{
	double	res;

	ft_printf("get_double b4 move line = |%s|\n", *line);
	res = 0;
	res = ft_atof(*line);
	ft_skip_num(line, REAL);
	ft_printf("res = %f: get_double after move line = |%s|\n", res, *line);
	if (mode == RATIO && 0 <= res && res <= 1)
	{
		printf("from ratio res: %f, left: %s\n", res, *line);
		return (res);
	}
	else if (mode == REAL)
	{
		printf("from ratio res: %f, left: %s\n", res, *line);
		return (res);
	}
	else if (mode == BALANCE && -1 <= res && res <= 1)
	{
		printf("from ratio res: %f, left: %s\n", res, *line);
		return (res);
	}
	else if (mode == ANGLE && 0 <= res && res <= 180)
	{
		printf("from ratio res: %f, left: %s\n", res, *line);
		return (res);
	}
	else
		ft_error(num_err);
	return (DBL_MAX);
}

t_vec3	get_vec3(char **line)
{
	t_vec3	vec;

	printf("in vec3\n");
	ft_skip_ws(line);
	vec.x = ft_atof(*line);
	printf("vec.x = %f\n", vec.x);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	if (**line == ',') 
		*line += 1; //added in to skip ','
	vec.y = ft_atof(*line);
	printf("vec.y = %f\n", vec.y);
	ft_skip_num(line, REAL);
	ft_skip_ws(line);
	if (**line == ',')
		*line += 1; 
	vec.z = ft_atof(*line);
	printf("vec.z = %f\n", vec.z);
	if (**line == '-') //not an elegant soloution to this issue
		*line += 1;
	ft_skip_num(line, REAL); //is getting stuck here at the camera positioning due to negative numbers '-'
	printf("leaving vec3\n");
	return (vec);
}
