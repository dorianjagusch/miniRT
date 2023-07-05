/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:16:11 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/05 18:58:05 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "libft.h"
# include <math.h>

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
t_vec3	vec3_add(const t_vec3 v, const t_vec3 u);
t_vec3	vec3_addf(const t_vec3 v, const double val);
t_vec3	vec3_sub(const t_vec3 v, const t_vec3 u);
t_vec3	vec3_subf(const t_vec3 v, const double val);
double	vec3_mag(const t_vec3 v);
t_vec3	vec3_multf(const t_vec3 v, const double val);
double	vec3_dot(const t_vec3 v, const t_vec3 u);
t_vec3	vec3_cross(const t_vec3 v, const t_vec3 u);
t_vec3	vec3_reflect(const t_vec3 v, const t_vec3 normal);
t_vec3	vec3_rotate(const t_vec3 vec, const t_vec3 normal);
t_vec3	vec3_compmult(const t_vec3 v, const t_vec3 u);
double	vec3_dist(const t_vec3 v1, const t_vec3 v2);
int		vec3_isnan(const t_vec3 v);
t_vec3	vec3_neg(const t_vec3 v);
void	vec3_normalize(t_vec3 *v);
void	vec3_scale(t_vec3 *v, const t_range old, const t_range new);
void	vec3_clamp(t_vec4 *v, const double min, const double max);

t_vec4	vec4_add(const t_vec4 v, const t_vec4 u);
t_vec4	vec4_addf(const t_vec4 v, const double val);
t_vec4	vec4_sub(const t_vec4 v, const t_vec4 u);
t_vec4	vec4_subf(const t_vec4 v, const double val);
double	vec4_mag(const t_vec4 v);
t_vec4	vec4_multf(const t_vec4 v, const double val);
double	vec4_dot(const t_vec4 v, const t_vec4 u);
t_vec4	vec4_propadd(const t_vec4 v1, const t_vec4 v2, const double prop);
t_vec4	vec4_compmult(const t_vec4 v, const t_vec4 u);
int		vec4_isnan(const t_vec4 v);
void	vec4_clamp(t_vec4 *v, const double min, const double max);
void	vec4_scale(t_vec4 *v, const t_range old, const t_range new);

void	ft_rgbtonorm(t_vec4 *colour);
t_vec4	ft_trgbtov4(int colour[4]);
t_vec4	ft_int32tov4(int32_t colour);
int32_t	vec4_toint32(t_vec4 colour);
#endif
