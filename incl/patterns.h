/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:03:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/13 19:29:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H

# include "vector_math.h"
# include "minirt.h"

typedef struct s_checker_board
{
	t_vec4	light;
	t_vec4	dark;
	int		width;
	int		height;
}			t_checker_board;


typedef struct s_picture
{
	t_vec4	light;
	t_vec4	dark;
	int		width;
	int		height;
}			t_picture;

typedef	union s_map
{
	
}			t_map;


#endif