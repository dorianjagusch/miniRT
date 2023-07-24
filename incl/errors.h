/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/24 11:06:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>

enum e_errors
{
	file_err = 160,
	num_err,
	range_err,
	ident_err,
	content_err,
	unique_err,
	object_open_err,
	xpm_err,
};

// Bitmapping image info
# define NAME_INIT 0x80
# define WIN_INIT 0x40
# define WIN_WIN_INIT 0x20
# define WIN_MLX_INIT 0x10
# define OBJ_INIT 0x08
# define COLOUR_INIT 0x04
# define IMG_INIT 0x02
# define ADDR_INIT 0x01

// Bitmapping window activity
# define WIN_3 0x08
# define WIN_2 0x04
# define WIN_1 0x02
# define WIN_0 0x01

void	ft_error(int error);

#endif