/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:54:49 by abenani           #+#    #+#             */
/*   Updated: 2021/02/06 16:03:54 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void render(t_color *img_buff, t_obj *obj)
{
    float i;
    float j;
    float ratio;
    int num;
    t_cam cam;
    t_vec cam_pos;
    t_vec look_at;

    
    t_color test = {0,255,0,255};
    cam_pos = vec_add(objvec(obj->obj[0]), objvec(obj->obj[1]));
    look_at = vec_add(objvec(obj->obj[2]), objvec(obj->obj[1]));
    cam = cam_mx(cam_pos, look_at);

    // t_vec new = camera_transform(cam, vec(0, 0, -1), cam_pos);
    // printf("(%f,%f,%f)\n", new.x, new.y, new.z);


    
    

    ratio = W_WIDTH / W_HEIGHT;
    j = 0;
    while (j < W_HEIGHT)
    {
        i = 0;
        while(i < W_WIDTH)
        {
            float x = (2*((i+.5)/W_WIDTH)-1) * ratio;
            float y = 1-2*((j+.5)/W_HEIGHT);
            // printf("[%.4f , %.4f] ", x, y);
            num = W_WIDTH * j + i;
            img_buff[num] =  test; // function to return the color 
            i++;
        }
        // printf("*\n");
        j++;
    }
}

t_cam  cam_mx(t_vec from, t_vec to)
{
    t_cam vecs;

    vecs.f = vec_unit(vec_add(from, vec_num(to, -1)));
    vecs.r = vec_unit(vec_cross(vec(0, 1, 0), vecs.f)); // (0, 1, 0) it will cause a problem (in case they are Parallel)
    vecs.u = vec_unit(vec_cross(vecs.f, vecs.r));
    return vecs;
}

t_vec   camera_transform(t_cam vecs, t_vec old_p, t_vec tr)
{
    t_vec   new_p;

    new_p.x = old_p.x * vecs.r.x + old_p.y * vecs.u.x + old_p.z * vecs.f.x + tr.x;
    new_p.y = old_p.x * vecs.r.y + old_p.y * vecs.u.y + old_p.z * vecs.f.y + tr.y;
    new_p.z = old_p.x * vecs.r.z + old_p.y * vecs.u.z + old_p.z * vecs.f.z + tr.z;
    return (new_p);
}

t_vec   objvec(int *arr)
{
    t_vec vect;
    
    vect  = vec(arr[0], arr[1], arr[2]);
    return vect;
}