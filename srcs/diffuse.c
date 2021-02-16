/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:25:05 by abenani           #+#    #+#             */
/*   Updated: 2021/02/16 18:25:47 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

t_vec cylinder_nrm(t_obj *obj, t_vec org, t_vec dir, double t, t_vec p)
{
    double m;
    t_vec v;
    t_vec x;
    t_vec c;
    t_vec a;

    v = vec_unit(objvec(obj->obj[4]));
    c =  objvec(obj->obj[0]);
    x = vec_sub(org, c);

    m = vec_dot(dir, v) * t + vec_dot(x, v);
    a = vec_add(c, vec_num(v, m));
    return vec_unit(vec_sub(p,a));
}
t_vec plane_nrm(t_obj *obj, t_vec org, t_vec dir)
{
    t_vec nrm;
    nrm = vec_unit(objvec(obj->obj[4]));
    if(vec_dot(dir, nrm) > 0)
        nrm = vec_num(nrm, -1);
    return nrm;
}
t_vec cone_nrm(t_obj *obj, t_vec org, t_vec dir, double t, t_vec p)
{
    t_vec nrm;

    return nrm;
}

t_color     diffuse(t_obj *obj, t_vec org, t_vec dir, double t)  
{
    t_vec light;
    t_color color;
    t_vec nrm;
    t_vec p;
    t_vec l;
    
    
    light.x = 0;
    light.y = 0;
    light.z = 0;
    
    p = vec_add(org, vec_num(dir, t));
    l = vec_unit(vec_sub(light, p));
    color = objcolor(obj->obj[2]);
    if(obj->id == 2)
        nrm = vec_unit(vec_sub(p, objvec(obj->obj[0])));
    if(obj->id == 3)
        nrm = plane_nrm(obj, org, dir);
    if(obj->id == 4)
        return color;
    if(obj->id == 5)
        nrm = cylinder_nrm(obj, org, dir, t, p);
    double diff = vec_dot(nrm, l);
    if(diff < 0)
        diff = 0;
    color.r *= diff; 
    color.g *= diff; 
    color.b *= diff;
    return (color);
}