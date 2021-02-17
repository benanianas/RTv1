/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:14:46 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/17 10:50:24 by moel-aza         ###   ########.fr       */
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

    sp.t = 0;
    sp.rad = sphere->oneint;
    sp.pos = objvec(sphere->obj[0]);
    sp.x = vec_sub(org, sp.pos);
    sp.t = -1;
    sol.a = vec_dot(dir, dir);
    sol.b = 2 * vec_dot(dir, sp.x);
    sol.c = vec_dot(sp.x, sp.x) - sp.rad * sp.rad;
    sol.delta = sol.b*sol.b - 4*sol.a*sol.c; 
    if( sol.delta > 0)
    { 
        sp.t = (-sol.b + sqrt(sol.delta))/2*sol.a;
        tmp = (-sol.b - sqrt(sol.delta))/2*sol.a;
        if(tmp < sp.t)
            sp.t = tmp;
    }
    return sp.t;
}

t_vec rotation(t_vec v,int *rot)
{
    t_vec ang;
    t_vec ret;

    ang = vec_num(objvec(rot), (float)PI/180);
    ret.x = v.x * cos(ang.z) - v.y * sin(ang.z);
    ret.y = v.x * sin(ang.z) + v.y * cos(ang.z);
    ret.z = v.z;
    v = ret;
 
    ret.x = v.x * cos(ang.y) + v.z * sin(ang.y);
    ret.y = v.y;
    ret.z = -v.x * sin(ang.y) + v.z * cos(ang.y);
    v = ret;


    ret.x = v.x;
    ret.y = v.y * cos(ang.x) - v.z * sin(ang.x);
    ret.z = v.y * sin(ang.x) + v.z * cos(ang.x);
    v = ret;
   
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
    // cyl.nrm = vec_unit(objvec(cylinder->obj[4]));
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
int		ft_min_ray(float t1, float t2, float *t)
{
	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	return (0);
}

double cone(t_obj *cone, t_vec org, t_vec dir)
{
    
    t_eq	d;
	float	c;
    float tmin = INFINITY;
	d.x = vec_sub(org, objvec(cone->obj[0]));
	d.k = tanf(cone->oneint*M_PI/360);
	d.a = vec_dot(dir, dir) - (1. + d.k * d.k) * \
		powf(vec_dot(dir, objvec(cone->obj[4])), 2.);
	d.b = 2.0 * (vec_dot(dir, d.x) - ((1. + d.k * d.k) * \
				vec_dot(dir, objvec(cone->obj[4])) * vec_dot(d.x, objvec(cone->obj[4]))));
	c = vec_dot(d.x, d.x) - (1. + d.k * d.k) * powf(vec_dot(d.x, objvec(cone->obj[4])), 2.);
	d.delta = (d.b * d.b) - (4.0 * d.a * c);
	if (d.delta < 0)
		return (0);
	d.delta = sqrtf(d.delta);
	d.t1 = (-d.b + d.delta) / (2 * d.a);
	d.t2 = (-d.b - d.delta) / (2 * d.a);
	return (ft_min_ray(d.t1, d.t2, &tmin));
    
    // t_shape cn;
    // t_eq sol;
    // double t1;
    // double anng;
    
    // anng = (double)cone->oneint;
    // cn.t = 0;
    // cn.nrm = vec_unit(objvec(cone->obj[4])); // v
    // cn.ang = tan(anng * (PI / 360)); // k
    // cn.x = vec_sub(org, objvec(cone->obj[0])); //X
    // sol.a = vec_dot(dir,dir) - (1 + cn.ang * cn.ang) * vec_dot(dir,cn.nrm) * vec_dot(dir,cn.nrm);
    // sol.b = 2.0*(vec_dot(dir,cn.x) - (1 + cn.ang * cn.ang) * vec_dot(dir,cn.nrm) * vec_dot(cn.x,cn.nrm));
    // sol.c = vec_dot(cn.x,cn.x) - (1 + cn.ang * cn.ang) * vec_dot(cn.x,cn.nrm) * vec_dot(cn.x,cn.nrm);
    // sol.delta = sol.b * sol.b - (4.0 * sol.a * sol.c);
    // if(sol.delta > 0)
    // {
    //     cn.t = (- sol.b - sqrt(sol.delta))/(2.0 * sol.a);
    //     cn.tmp =  (- sol.b + sqrt(sol.delta))/(2.0 * sol.a);
    //     if(cn.tmp < cn.t)
    //         cn.t = cn.tmp;
    // }
    // return cn.t;
}