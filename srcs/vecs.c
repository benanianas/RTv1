/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:25:34 by abenani           #+#    #+#             */
/*   Updated: 2021/01/31 13:00:33 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

t_vec   vec(double x, double y, double z)
{
    t_vec vec;
    
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}

t_vec   vec_dot(t_vec a, t_vec b)
{
    t_vec ret;

    ret.x = a.x * b.x;
    ret.y = b.x * b.y;
    ret.z = a.z * b.z;
    return (ret);
}

t_vec   vec_cross(t_vec a, t_vec b)
{
    t_vec ret;
    
    ret.x = a.y * b.z - a.z * b.y;
    ret.y = a.z * b.x - a.x * b.z;
    ret.z = a.x * b.y - a.y * b.x;
    return (ret);
}

double  vec_magnitude(t_vec vec)
{
    t_vec   ret;
    
    ret = vec_dot(vec, vec);
    return (sqrt(ret.x + ret.y + ret.z));
}

t_vec   vec_unit(t_vec vec)
{
    t_vec ret;
    double mgn;
    
    mgn = vec_magnitude(vec);
    
    ret.x = vec.x/mgn;
    ret.y = vec.y/mgn;
    ret.z = vec.z/mgn;
    
    return (ret);
}

t_vec   vec_add(t_vec a, t_vec b)
{
    t_vec ret;

    ret.x = a.x = b.x;
    ret.y = a.y = b.y;
    ret.z = a.z = b.z;
    return (ret);
}