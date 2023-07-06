/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/29 12:13:49 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print_helpers.h"


int	main(int ac, char **av)
{
	t_img	img;


	if (ac > 2 || av[1] == 0)
		ft_error(E2BIG);
	if (!ft_strncmp(av[1], "H", 2))
		ft_options();
	ft_bzero(&img, sizeof(img));
	if (!ft_strncmp(av[1] + strlen(av[1]) - 4, ".obj", 4) || \
		!ft_strncmp(av[1] + strlen(av[1]) - 4, ".stl", 4)) //TODO: how do we feel about the check been here?
		binary_set_scene(&(img.scene),  av[1]);
	else
		set_scene(&(img.scene), av[1]);
	validate_scene(&img.scene);
	print_scene(img.scene);
	set_image(&img);
	user_input(&img);
	render(&img);
	mlx_loop(img.win.mlx);
	return (0);
}
