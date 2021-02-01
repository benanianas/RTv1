/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:54:49 by abenani           #+#    #+#             */
/*   Updated: 2021/02/01 20:47:41 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

t_vecs  camera_matx(t_vec from, t_vec to)
{
    t_vecs vecs;

    vecs.f = vec_unit(vec_add(from, vec_num(to, -1)));
    vecs.r = vec_unit(vec_cross(vec(0, 1, 0), vecs.f)); // (0, 1, 0) it will cause a problem (forward parallel to it)
    vecs.u = vec_unit(vec_cross(vecs.f, vecs.r));
    
    //need to return the 3 vectors
    
    return vecs;
}

t_vec   camera_transform(t_vecs vecs, t_vec old_p, t_vec tr)
{
    t_vec   new_p;

    new_p.x = old_p.x * vecs.r.x + old_p.y * vecs.u.x + old_p.z * vecs.f.x + tr.x;
    new_p.y = old_p.x * vecs.r.y + old_p.y * vecs.u.y + old_p.z * vecs.f.y + tr.y;
    new_p.z = old_p.x * vecs.r.z + old_p.y * vecs.u.z + old_p.z * vecs.f.z + tr.z;

    return (new_p);
    
}