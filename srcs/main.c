/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/23 13:51:18 by djagusch         ###   ########.fr       */
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
	t_scene	scene;

	if (ac > 2 || av[1] == 0)
		ft_error(E2BIG);
	if (!ft_strncmp(av[1], "H", 2))
		ft_options();
	ft_bzero(&img, sizeof(img));
	set_image(&img);
	img.scene = &scene;
	set_scene(&img, img.scene, av[1]);
	validate_scene(img.scene);
	calloc_light_arrays(img.scene);
	print_scene(*(img.scene));
	user_input(&img);
	render(&img);
	mlx_loop(img.win.mlx);
	return (0);
}
