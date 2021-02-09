/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:54:49 by abenani           #+#    #+#             */
/*   Updated: 2021/02/09 11:23:44 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void render(t_color *img_buff, t_obj *obj)
{
    
    t_cam cam;
    t_vec cam_pos;
    t_vec look_at;
    
    
    t_color test = {0,255,0,255};
    cam_pos = vec_add(objvec(obj->obj[0]), objvec(obj->obj[1]));
    look_at = vec_add(objvec(obj->obj[2]), objvec(obj->obj[1]));
    cam = cam_mx(cam_pos, look_at);
    renderer_loop(img_buff, obj, cam);

    // t_vec new = camera_transform(cam, vec(0, 0, -1));
    // printf("(%f,%f,%f)\n", cam.pos.x, cam.pos.y, cam.pos.z );
    // printf("(%f,%f,%f)\n", new.x, new.y, new.z);
}

int         sphere(t_obj *sphere, t_vec org, t_vec dir)
{
    int rad = 1;
    t_vec center = objvec(sphere->obj[0]);
    t_vec x = vec_sub(org, center);

    double a = vec_dot(dir, dir);
    double b = 2 * vec_dot(dir, x);
    double c = vec_dot(x, x) - rad * rad;

    double delta = b*b - 4*a*c;
    if( delta >= 0)
        return (1);
    else
        return (0);  
}

t_color     pixel_fill(t_obj *object, t_vec org, t_vec dir)
{
    t_color test = {0,0,0,255};
    t_color color = {255, 0,0,255};
    t_obj *obj = object;
    
    while(obj)
    {
        if (obj->id == 2)
        {
            if(sphere(obj, org, dir))
                return color;
        }
        obj = obj->next;
    }
        
    return test;
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
            float x = (2*((float)(i+.5)/W_WIDTH)-1) * ratio;
            float y = 1-2*((float)(j+.5)/W_HEIGHT);
            pt = camera_transform(cam, vec(x, y, -1));
            num = W_WIDTH * j + i;
            img_buff[num] =  pixel_fill(obj, cam.pos, vec_unit(vec_sub(pt, cam.pos)));
            // printf("[%.4f , %.4f] ", x, y);
        }
        // printf("*\n");
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