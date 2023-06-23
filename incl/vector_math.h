/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorphet <smorphet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:16:11 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/23 11:42:14 by smorphet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "libft.h"

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
t_vec3	vec3_add(t_vec3 v, t_vec3 u);
t_vec3	vec3_addf(t_vec3 v, double val);
t_vec3	vec3_sub(t_vec3 v, t_vec3 u);
t_vec3	vec3_subf(t_vec3 v, double val);

double	vec3_mag(t_vec3 v);
t_vec3	vec3_multf(t_vec3 v, double val);
void	vec3_normalize(t_vec3 *v);
double	vec3_dot(t_vec3 v, t_vec3 u);
t_vec3	vec3_cross(t_vec3 v, t_vec3 u);
double	ft_cos_angle(t_vec3 v, t_vec3 u); //currently unused
t_vec3	vec3_reflect(t_vec3 v, t_vec3 normal);
void	vec3_scale(t_vec3 *v, t_range old, t_range new);
void	vec3_clamp(t_vec4 *v, double min, double max);

t_vec4	vec4_add(t_vec4 v, t_vec4 u);
t_vec4	vec4_addf(t_vec4 v, double val);
t_vec4	vec4_sub(t_vec4 v, t_vec4 u);
t_vec4	vec4_subf(t_vec4 v, double val);
t_vec4	vec4_multf(t_vec4 v, double val);
void	vec4_clamp(t_vec4 *v, double min, double max);
void	vec4_scale(t_vec4 *v, t_range old, t_range new);
void	ft_rgbtonorm(t_vec4 *colour);
t_vec4	ft_trgbtov4(int colour[4]);
t_vec4	ft_int32tov4(int32_t colour);
int32_t	vec4_toint32(t_vec4 colour);
#endif