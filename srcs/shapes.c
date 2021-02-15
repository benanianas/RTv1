/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:14:46 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/15 11:10:42 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

double plane(t_obj * plane, t_vec org, t_vec dir)
{
    t_plane pl;
    double numone;

    pl.point = vec_add(objvec(plane->obj[1]),objvec(plane->obj[0]));
    pl.nor = vec_unit(vec_add(objvec(plane->obj[3]) ,objvec(plane->obj[4])));
    if(vec_dot(dir,pl.nor) == 0)
        return 0;
    numone = 1/vec_dot(dir,pl.nor);
    pl.t = numone * (vec_dot(pl.point,pl.nor) - vec_dot(org,pl.nor));
    return (pl.t);
}

double      sphere(t_obj *sphere, t_vec org, t_vec dir)
{
    t_shape sp;
    t_eq sol;
    double tmp;

    sp.rad = sphere->oneint;
    sp.pos = objvec(sphere->obj[0]);
    sp.x = vec_sub(org, sp.pos);
    sp.t = -1;
    sol.a = vec_dot(dir, dir);
    sol.b = 2 * vec_dot(dir, sp.x);
    sol.c = vec_dot(sp.x, sp.x) - sp.rad * sp.rad;
    sol.delta = sol.b*sol.b - 4*sol.a*sol.c; 
    
    if(sol.delta == 0)
        sp.t = -sol.b/2*sol.a;
    else if( sol.delta > 0)
    { 
        sp.t = (-sol.b + sqrt(sol.delta))/2*sol.a;
        tmp = (-sol.b - sqrt(sol.delta))/2*sol.a;
        if(tmp < sp.t)
            sp.t = tmp;
    }
    if(sp.t <= 0)
        return 0;
    return sp.t;
}

t_vec rotation(t_vec v,int *rot)
{
    t_vec ang;
    t_vec ret;

    ang = vec_num(objvec(rot), (float)PI/180);
    if(ang.z)
    {
        ret.x = v.x * cos(ang.z) - v.y * sin(ang.z);
        ret.y = v.x * sin(ang.z) + v.y * cos(ang.z);
        ret.z = v.z;
        v = ret;
    }
    if(ang.y)
    {
        ret.x = v.x * cos(ang.y) + v.z * sin(ang.y);
        ret.y = v.y;
        ret.z = -v.x * sin(ang.y) + v.z * cos(ang.y);
        v = ret;
    }
    if(ang.x)
    {
        ret.x = v.x;
        ret.y = v.y * cos(ang.x) - v.z * sin(ang.x);
        ret.z = v.y * sin(ang.x) + v.z * cos(ang.x);
        v = ret;
    }
    return ret; 
}

double cylinder(t_obj *cylinder, t_vec org, t_vec dir)
{
    t_shape cyl;
    t_eq    sol;
    double  tmp;

    cyl.rad = cylinder->oneint;
    cyl.pos = objvec(cylinder->obj[0]);
    cyl.x = vec_sub(org, cyl.pos);
    cyl.nrm = rotation(vec_unit(objvec(cylinder->obj[4])), cylinder->obj[3]);
    cyl.t = 0;
    sol.a = vec_dot(dir, dir) - (vec_dot(dir, cyl.nrm) * vec_dot(dir, cyl.nrm));
    sol.b = 2 * (vec_dot(dir, cyl.x) - (vec_dot(dir, cyl.nrm) * vec_dot(cyl.x, cyl.nrm)));
    sol.c = vec_dot(cyl.x, cyl.x) - (vec_dot(cyl.x, cyl.nrm) * vec_dot(cyl.x, cyl.nrm)) - cyl.rad * cyl.rad;

    
    sol.delta = sol.b * sol.b - 4 * sol.a * sol.c; 
    
  
    if( sol.delta > 0)
    { 
        cyl.t = (-sol.b + sqrt(sol.delta))/2 * sol.a;
        tmp = (-sol.b - sqrt(sol.delta))/2 * sol.a;
        if(tmp < cyl.t)
            cyl.t = tmp;
    }
    return cyl.t;
}