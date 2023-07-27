/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/27 08:01:22 by djagusch         ###   ########.fr       */
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
	unique_err
};

void	ft_error(int error);

#endif