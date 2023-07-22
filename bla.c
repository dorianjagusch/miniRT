/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bla.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:07:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/22 17:09:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	main(void)
{
	int	fd;
	int	i;

	fd = open("textures/colour/151.xpm", O_RDONLY);
	i = 0;
	while (i < 12)
	{
		printf("%s\n", get_next_line(fd));
		i++;
	}
	close (fd);
	return (0);
}
