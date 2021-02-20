/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:25:34 by abenani           #+#    #+#             */
/*   Updated: 2021/02/20 12:09:13 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

t_vec		vec(double x, double y, double z)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double		vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec		vec_cross(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

double		vec_magnitude(t_vec vec)
{
	return (sqrt(vec_dot(vec, vec)));
}

t_vec		vec_unit(t_vec vec)
{
	t_vec	ret;
	double	mgn_ivt;

	mgn_ivt = 1.0 / vec_magnitude(vec);
	ret.x = vec.x * mgn_ivt;
	ret.y = vec.y * mgn_ivt;
	ret.z = vec.z * mgn_ivt;
	return (ret);
}

t_vec		vec_add(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec		vec_sub(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec		vec_num(t_vec vec, double num)
{
	t_vec ret;

	ret.x = vec.x * num;
	ret.y = vec.y * num;
	ret.z = vec.z * num;
	return (ret);
}
