/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/02/01 20:47:19 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void render(t_color *colors)
{
    float i;
    float j;
    
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
            colors[num] =  test;
            i++;
        }
        // printf("*\n");
        j++;
    }
}

int main(int ac, char **av)
{
    // t_sdl sdl;
    // t_color *colors;
    // colors = malloc(W_WIDTH * W_HEIGHT * sizeof(t_color));
   
    // if(!startSdl(&sdl))
    //     exit (0);
    // render(colors);
    // draw(sdl.rend, colors);
    // while(1)
    //     if(exitSdl(sdl))
    //         break;
    t_vec point;

    point.x = 0;
    point.y = 0;
    point.z = -1;
    
    t_vec from;
    from.x = 0;
    from.y = 0;
    from.z = 0;
    
    t_vec to;
    to.x = 0;
    to.y = 0;
    to.z = -1;

    t_vecs vecs = camera_matx(from, to);

    t_vec new = camera_transform(vecs, point, from);

    printf("(%f,%f,%f)\n", new.x, new.y, new.z);
    
    
    return 0;
}