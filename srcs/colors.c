/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:25:05 by abenani           #+#    #+#             */
/*   Updated: 2021/02/16 23:38:00 by abenani          ###   ########.fr       */
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

t_color     light_pixel(t_obj *obj, t_vec org, t_vec dir, double t)  
{
    t_vec light;
    t_color color;
    t_color light_c;
    t_vec nrm;
    t_vec p;
    t_vec l;
    
    int light_int = obj->head->next->oneint;
    light_c = objcolor(obj->head->next->obj[2]);
    light = objvec(obj->head->next->obj[0]);
    color = objcolor(obj->obj[2]);
    
    //anbient 
    color.r = color.r ;//+ light_c.r;
    color.g = color.g ;//+ light_c.g;
    color.b = color.b ;//+ light_c.b;

    //diffuse
    
    p = vec_add(org, vec_num(dir, t));
    l = vec_unit(vec_sub(light, p));
       if(obj->id == 2)
        nrm = vec_unit(vec_sub(p, objvec(obj->obj[0])));
    if(obj->id == 3)
        nrm = plane_nrm(obj, org, dir);
    double diff = vec_dot(nrm, l);
    if(diff < 0)
        diff = 0;
    color.r *= diff; 
    color.g *= diff; 
    color.b *= diff;

    //specular

    t_vec h;
    t_vec c = vec_sub(org, p);

    h = vec_unit(vec_add(c, l));
    double spec = vec_dot(nrm, h);
    if(spec < 0)
        spec = 0;
    color.r *= pow(spec, 66); 
    color.g *= pow(spec, 66); 
    color.b *= pow(spec,66); 
    return (color);
}
