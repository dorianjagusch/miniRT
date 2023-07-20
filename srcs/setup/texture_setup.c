/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:49:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/20 13:22:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"
#include "errors.h"

void	set_meta(t_object *object)
{
	object->meta.texture = ft_calloc(1, sizeof(t_texture));
	if (!object->meta.texture)
		ft_error(ENOMEM);
	object->meta.texture->checkers = set_board(10, 10, object->meta.colour,
			vec4_multf(object->meta.colour, 0.5));
	object->meta.texture->pattern = brick_pat;
}
