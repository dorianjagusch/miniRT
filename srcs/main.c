/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 10:46:56 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"

void	calloc_light_arrays(t_scene	*scene)
{
	scene->distances = ft_calloc(sizeof(float), scene->n_lights);
	scene->directions = ft_calloc(sizeof(t_vec3), scene->n_lights);
	scene->specular = ft_calloc(sizeof(t_vec4), scene->n_lights);
	if (!scene->distances || !scene->directions)
		ft_error(ENOMEM);
}	

int	main(int ac, char **av)
{
	t_img	img;

	if (ac > 2 || av[1] == 0)
		ft_error(E2BIG);
	ft_bzero(&img, sizeof(img));
	set_scene(&(img.scene), av[1]);
	validate_scene(&img.scene);
	calloc_light_arrays(&img.scene);
	print_scene(img.scene);
	set_image(&img);
	user_input(&img);
	render(&img);
	mlx_loop(img.win.mlx);
	return (0);
}
