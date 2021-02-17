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
    
    float light_int = obj->head->next->oneint;
    light_c = objcolor(obj->head->next->obj[2]);
    light = objvec(obj->head->next->obj[0]);
    color = objcolor(obj->obj[2]);
    
    //anbient
    light_int = (light_int < 0) ? 0:light_int;
    light_int = (light_int > 255) ? 255:light_int;
    light_int = light_int;
    
    color.a = light_int;
    // light_int /= 1500;
    color.r = 0.5 * color.r + (light_int / 1500) * light_c.r;
    color.g = 0.5 * color.g + (light_int / 1500) * light_c.g;
    color.b = 0.5 * color.b + (light_int / 1500) * light_c.b;

    // diffuse

    p = vec_add(org, vec_num(dir, t));
    l = vec_unit(vec_sub(light, p));
       if(obj->id == 2)
        nrm = vec_unit(vec_sub(p, objvec(obj->obj[0])));
    if(obj->id == 3)
        nrm = plane_nrm(obj, org, dir);
    double diff = vec_dot(nrm, l)*(light_int / 170);
    if(diff < 0)
        diff = 0;
    
    color.r *= diff; 
    color.g *= diff; 
    color.b *= diff;

    //specular

    // t_vec h;
    // t_vec c = vec_sub(org, p);

    // h = vec_unit(vec_add(c, l));
    // double spec = vec_dot(nrm, h);
    // if(spec < 0)
    //     spec = 0;
    // spec = pow(spec, 128);
    // color.r *= spec; 
    // color.g *= spec; 
    // color.b *= spec; 



    return (color);
}
