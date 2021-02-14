/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:14:46 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/14 17:26:42 by moel-aza         ###   ########.fr       */
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
// double cone(t_obj * cone, t_vec org, t_vec dir)
// {
//     t_cone con;
//     double a;
//     double b;
//     double c;
//     double dt;
//     double t;
//     double tmp;
    
//     con.d = dir;
//     con.v = vec_unit(objvec(cone->obj[4]));
//     con.co = vec_sub(org,objvec(cone->obj[0]));
//     con.ang = (double)cone->oneint/2 * M_PI/180;

//     a = (vec_dot(con.d, con.v) * vec_dot(con.d, con.v)) - (cos(con.ang) * cos(con.ang));
//     b = 2*((vec_dot(con.d, con.v))*(vec_dot(con.co, con.v)) - (vec_dot(con.d, vec_num(con.co ,cos(con.ang) * cos(con.ang)))));
//     c = ((vec_dot(con.co, con.v) * vec_dot(con.co, con.v)) - (vec_dot(con.co, vec_num(con.co , cos(con.ang) * cos(con.ang)))));
//     dt = (b * b) - (4*a*c);
   
//     if (dt > 0)
//     {
//         t = (-b - sqrt(dt)) / (2 * a);
//         tmp = (-b + sqrt(dt)) / (2 * a);
//         if(tmp > t)
//             t = tmp;
//         return t;
//     }
//     return 0;
// }

double cone(t_obj *cone, t_vec org, t_vec dir)
{
    t_shape cn;
    t_eq sol;
    double t1;
    double anng;
    
    anng = (double)cone->oneint;
    cn.t = 0;
    cn.nrm = vec_unit(objvec(cone->obj[4])); // v
    cn.ang = tan(anng * (M_PI / 360)); // k
    cn.x = vec_sub(org, objvec(cone->obj[0])); //X
    sol.a = vec_dot(dir,dir) - (1 + cn.ang * cn.ang) * vec_dot(dir,cn.nrm) * vec_dot(dir,cn.nrm);
    sol.b = 2.0*(vec_dot(dir,cn.x) - (1 + cn.ang * cn.ang) * vec_dot(dir,cn.nrm) * vec_dot(cn.x,cn.nrm));
    sol.c = vec_dot(cn.x,cn.x) - (1 + cn.ang * cn.ang) * vec_dot(cn.x,cn.nrm) * vec_dot(cn.x,cn.nrm);
    
    sol.delta = sol.b * sol.b - (4.0 * sol.a * sol.c);
    if(sol.delta == 0)
    {
        return( - sol.b /  2.0 * sol.a);
    }
    if(sol.delta > 0)
    {
        cn.t = (- sol.b - sqrt(sol.delta))/(2.0 * sol.a);
        cn.tmp =  (- sol.b + sqrt(sol.delta))/(2.0 * sol.a);
        if(cn.tmp < cn.t)
            cn.t = cn.tmp;
    }
    return cn.t;
}