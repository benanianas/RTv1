/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:54:49 by abenani           #+#    #+#             */
/*   Updated: 2021/02/16 12:42:59 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void render(t_color *img_buff, t_obj *obj)
{
    
    t_cam cam;
    t_vec cam_pos;
    t_vec look_at;
    
    
    cam_pos = vec_add(objvec(obj->obj[0]), objvec(obj->obj[1]));
    look_at = vec_add(objvec(obj->obj[2]), objvec(obj->obj[1]));
    cam = cam_mx(cam_pos, look_at);
    renderer_loop(img_buff, obj, cam);
}

t_color     pixel_fill(t_obj *object, t_vec org, t_vec dir)
{
    t_color black = {0,0,0,255};
    t_obj *obj = object;
    double t = INFINITY;
    double tmp;
    t_obj  *theobj;
    
    tmp = 0;
    while(obj)
    {
        if (obj->id == 2)
            tmp = sphere(obj, org, dir);
        else if(obj->id == 3)
            tmp = plane(obj, org, dir);
        else if(obj->id == 5)
            tmp = cylinder(obj, org, dir);
        else if(obj->id == 4)
            tmp = cone(obj, org, dir);
        if(tmp > 0 && tmp < t)
        {
            t = tmp;
            theobj = obj;
        }
        obj = obj->next;
    }
    
    if(t < INFINITY)
        return  diffuse(theobj, org, dir, t);
    return black;
}

void    renderer_loop(t_color *img_buff, t_obj *obj, t_cam cam)
{
    int i;
    int j;
    float ratio;
    int num;
    t_vec pt;
    
    ratio = (float)W_WIDTH / W_HEIGHT;
    j = -1;
    while (++j < W_HEIGHT)
    { 
        i = -1;
        while(++i < W_WIDTH)
        {
            float x = ((2*((float)(i+.5)/W_WIDTH)-1) * ratio) * 2;
            float y = (1-2*((float)(j+.5)/W_HEIGHT)) * 2;
            pt = camera_transform(cam, vec(x, y, -1));
            num = W_WIDTH * j + i;
            img_buff[num] =  pixel_fill(obj, cam.pos, vec_unit(vec_sub(pt, cam.pos)));
        }
    }
}


t_cam  cam_mx(t_vec from, t_vec to)
{
    t_cam vecs;

    vecs.f = vec_unit(vec_add(from, vec_num(to, -1)));
    vecs.r = vec_unit(vec_cross(vec(0, 1, 0), vecs.f)); // (0, 1, 0) it will cause a problem (in case they are Parallel)
    vecs.u = vec_unit(vec_cross(vecs.f, vecs.r));
    vecs.pos = from;
    return vecs;
}

t_vec   camera_transform(t_cam cam, t_vec old_p)
{
    t_vec   new_p;

    new_p.x = old_p.x * cam.r.x + old_p.y * cam.u.x + old_p.z * cam.f.x + cam.pos.x;
    new_p.y = old_p.x * cam.r.y + old_p.y * cam.u.y + old_p.z * cam.f.y + cam.pos.y;
    new_p.z = old_p.x * cam.r.z + old_p.y * cam.u.z + old_p.z * cam.f.z + cam.pos.z;
    return (new_p);
}

t_vec   objvec(int *arr)
{
    t_vec vect;
    
    vect  = vec(arr[0], arr[1], arr[2]);
    return vect;
}

t_color     objcolor(int *arr)
{
    t_color col;
    
    col.r = arr[0];
    col.g = arr[1];
    col.b = arr[2];
    col.a = 255;
    return col;
}