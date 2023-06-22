/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/22 13:25:10 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_img	img;

	if (ac > 2 || av[1] == 0)
		ft_error(E2BIG);
	if (!ft_strncmp(av[1], "H", 2))
		ft_options();
	ft_bzero(&img, sizeof(img));
	set_scene(&(img.scene), av[1]);
	user_input(&img);
	render(&img);
	mlx_loop(img.win->mlx);
	return (0);
}
