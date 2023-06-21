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
void	ft_v3norm(t_vec3 *v);
double	ft_v3dot(t_vec3 v, t_vec3 u);
t_vec3	ft_cross(t_vec3 v, t_vec3 u); //currently unused
double	ft_cos_angle(t_vec3 v, t_vec3 u); //currently unused
t_vec3	ft_v3reflect(t_vec3 v, t_vec3 normal);
void	ft_v3scale(t_vec3 *v, t_range old, t_range new); //currently unused
void	ft_v3clamp(t_vec4 *v, double min, double max);

t_vec4	ft_v4add(t_vec4 v, t_vec4 u);
t_vec4	ft_v4addf(t_vec4 v, double val);
t_vec4	ft_v4sub(t_vec4 v, t_vec4 u);
t_vec4	ft_v4subf(t_vec4 v, double val);
t_vec4	ft_v4multf(t_vec4 v, double val);
void	ft_v4clamp(t_vec4 *v, double min, double max);
void	ft_v4scale(t_vec4 *v, t_range old, t_range new);
void	ft_rgbtonorm(t_vec4 *colour);
t_vec4	ft_trgbtov4(int colour[4]);
t_vec4	ft_int32tov4(int32_t colour);
int32_t	ft_v4toint32(t_vec4 colour);
#endif
