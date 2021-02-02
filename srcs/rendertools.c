/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:54:49 by abenani           #+#    #+#             */
/*   Updated: 2021/02/02 11:45:22 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void render(t_color *img_buff)
{
    float i;
    float j;
    t_cam tr_vecs;
    
    int w = W_WIDTH;
    int h = W_HEIGHT;
    float ratio = w / h;
    
    //to remove
    //*******//
    t_color test;
    test.r = 0;
    test.g = 0;
    test.b = 255;
    test.a = 255;
    /////////////

    // tr_vecs vecs = cam_mx(pos, look_at)

    j = 0;
    while (j < h)
    {
        i = 0;
        while(i < w)
        {
            float x = (2*((i+.5)/w)-1) * ratio ; 
            float y = 1-2*((j+.5)/h);
            // printf("[%.4f , %.4f] ", x, y);
            int num = w*j+i;
            img_buff[num] =  test;
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
    
    //need to return the 3 vectors
    
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