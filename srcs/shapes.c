/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:14:46 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/12 12:59:46 by abenani          ###   ########.fr       */
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

double cylinder(t_obj *cylinder, t_vec org, t_vec dir)
{
    t_shape cyl;
    t_eq    sol;
    double  tmp;

    cyl.rad = cylinder->oneint;
    cyl.pos = objvec(cylinder->obj[0]);
    cyl.x = vec_sub(org, cyl.pos);
    cyl.nrm = vec_unit(objvec(cylinder->obj[4])); // need to make the rotation function
    cyl.t = -1;
    sol.a = vec_dot(dir, dir) - (vec_dot(dir, cyl.nrm) * vec_dot(dir, cyl.nrm));
    sol.b = 2 * (vec_dot(dir, cyl.x) - (vec_dot(dir, cyl.nrm) * vec_dot(cyl.x, cyl.nrm)));
    sol.c = vec_dot(cyl.x, cyl.x) - (vec_dot(cyl.x, cyl.nrm) * vec_dot(cyl.x, cyl.nrm)) - cyl.rad * cyl.rad;

    
    sol.delta = sol.b * sol.b - 4 * sol.a * sol.c; 
    
    if(sol.delta == 0)
        cyl.t = -sol.b/2 * sol.a;
    else if( sol.delta > 0)
    { 
        cyl.t = (-sol.b + sqrt(sol.delta))/2 * sol.a;
        tmp = (-sol.b - sqrt(sol.delta))/2 * sol.a;
        if(tmp < cyl.t)
            cyl.t = tmp;
    }
    if(cyl.t <= 0)
        return 0;
    return cyl.t;
}