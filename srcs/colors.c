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
    t_vec v;
    t_vec c;
    t_vec x;
    double m;

    v = vec_unit(objvec(obj->obj[4]));
    c = objvec(obj->obj[0]);
    x = vec_sub(org, c);
    m = vec_dot(vec_unit(dir), v) * t + vec_dot(x, v);
    return (vec_unit(vec_sub(p, vec_add(c, vec_num(v, m)))));
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
    t_vec c;
    t_vec v;
    t_vec x;
    double k;
    double m;

    x = vec_sub(org, objvec(obj->obj[0]));
    k = tan(obj->oneint * (PI / 360));
    v = vec_unit(objvec(obj->obj[4]));
    c = objvec(obj->obj[0]);
    m = vec_dot(dir,vec_num(v, t)) + vec_dot(x,v);
    nrm = vec_unit(vec_sub(vec_sub(p,c) , vec_num (vec_num(v,(1+k*k)), m)));
    return nrm;
}

int     pixel_shadow(t_obj *obj, t_vec p, t_vec light)
{
    double t;
    double light_dst;
    double tmp;
    t_vec dir;
    
    dir = vec_unit(vec_sub(light, p));
    light_dst =  vec_magnitude(vec_sub(light, p));
    t = light_dst;
    tmp = 0;
    while(obj)
    {
        if (obj->id == 2)
            tmp = sphere(obj, p, dir);
        if(obj->id == 3)
            tmp = plane(obj, p, dir);
        else if(obj->id == 5)
            tmp = cylinder(obj, p, dir);
        else if(obj->id == 4)
            tmp = cone(obj, p, dir);
        if(tmp > 0 && tmp < t)
            t = tmp;
        obj = obj->next;
    }
    return (t < light_dst) ? 1:0;
}

t_color     ambient_color(t_obj *obj)
{
    t_color light_c;
    t_color color;
    float light_int;

    light_int = obj->head->next->oneint;
    light_int = (light_int < 0) ? 0:light_int; //********
    light_int = (light_int > 255) ? 255:light_int;
    color = objcolor(obj->obj[2]);
    light_c = objcolor(obj->head->next->obj[2]);
    color.a = light_int;
    color.r = 0.5 * color.r + (light_int / 1500) * light_c.r;
    color.g = 0.5 * color.g + (light_int / 1500) * light_c.g;
    color.b = 0.5 * color.b + (light_int / 1500) * light_c.b;
    return color;
}

// double      diffuse_color(t_obj *obj, t_vec org, t_vec dir, double t)
// {
   
// }

t_color     light_pixel(t_obj *obj, t_vec org, t_vec dir, double t)  
{
    t_vec light;
    t_color color;
    float light_int;
    t_vec nrm;
    t_vec p;
    t_vec l;
    double diff;
    
    light = objvec(obj->head->next->obj[0]);
    light_int = obj->head->next->oneint;
    color = objcolor(obj->obj[2]);
    light_int = (light_int < 0) ? 0:light_int;
    light_int = (light_int > 255) ? 255:light_int;
    
    color = ambient_color(obj);

    // diffuse

    p = vec_add(org, vec_num(dir, t));
    l = vec_unit(vec_sub(light, p));
    if(obj->id == 2)
        nrm = vec_unit(vec_sub(p, objvec(obj->obj[0])));
    if(obj->id == 3)
        nrm = plane_nrm(obj, org, dir);
    if(obj->id == 5)
        nrm = cylinder_nrm(obj, org, dir, t, p);
    if(obj->id == 4)
        nrm = cone_nrm(obj, org, dir, t, p);
    
    
    diff = vec_dot(nrm, l)*(light_int / 170);
    if(diff < 0)
        diff = 0;
  
    // diff = diffuse_color(obj, org, dir, t);

    //specular

    t_vec h;
    t_vec c = vec_sub(org, p);

    h = vec_unit(vec_add(vec_unit(c), vec_unit(l)));
    double spec = vec_dot(nrm, h);
    if(spec < 0)
        spec = 0;
    
    spec = pow(spec, 64);
    // spec = 0;
  

    t_obj *lp;
    lp = obj->head->next->next;

    while(lp)
    {
        if(lp != obj)
        {
            if(pixel_shadow(lp, p,light))
            {
                color.a = 100;
                spec = 0;
            }
        }
            
        lp = lp->next;
    }
    color.r *= (spec*2+diff); 
    color.g *= (spec*2+diff); 
    color.b *= (spec*2+diff); 

      if (color.r > 255)
        color.r = 255;
    if (color.g > 255)
        color.g = 255;
    if (color.b > 255)
        color.b = 255;

        if (color.r < 0)
        color.r = 0;
    if (color.g < 0)
        color.g = 0;
    if (color.b < 0)
        color.b = 0;
    return (color);
}