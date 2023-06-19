/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:16:11 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/18 17:38:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
    #define VECTOR_H

#include "libft.h"

typedef struct s_vec2
{
	double	x;
	double	y;
}			t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

typedef struct s_vec4
{
	double	v;
	double	x;
	double	y;
	double	z;
}			t_vec4;

// VECTOR MATHS
t_vec3	ft_v3add(t_vec3 v, t_vec3 u);
t_vec3	ft_v3addf(t_vec3 v, double val);
t_vec3	ft_v3sub(t_vec3 v, t_vec3 u);
t_vec3	ft_v3subf(t_vec3 v, double val);

double	ft_v3mag(t_vec3 v);
t_vec3	ft_v3multf(t_vec3 v, double val);
double	ft_v3norm(t_vec3 *v);
double	ft_v3dot(t_vec3 v, t_vec3 u);
t_vec3	ft_cross(t_vec3 v, t_vec3 u);
double	ft_cos_angle(t_vec3 v, t_vec3 u);
t_vec3	ft_reflect(t_vec3 v, t_vec3 normal);

t_vec4	ft_v4add(t_vec4 v, t_vec4 u);
t_vec4	ft_v4addf(t_vec4 v, double val);
t_vec4	ft_v4sub(t_vec4 v, t_vec4 u);
t_vec4	ft_v4subf(t_vec4 v, double val);
t_vec4	ft_v4multf(t_vec4 v, double val);

#endif
