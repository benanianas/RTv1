/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/01/29 13:44:40 by abenani          ###   ########.fr       */
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
    
    // t_color *colors;
    // colors = malloc(w * h * sizeof(t_color));
    t_color test;
    // test = {0, 255, 0 , 255}
    test.r = 0;
    test.g = 255;
    test.b = 0;
    test.a = 255;

    j = 0;
    while (j < h)
    {
        i = 0;
        while(i < w)
        {
            float x = (2*((i+.5)/w)-1) * ratio ;// *Zoom 
            float y = 1-2*((j+.5)/h);// *Zoom
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
    t_sdl sdl;
    t_color *colors;
    colors = malloc(W_WIDTH * W_HEIGHT * sizeof(t_color));
   
    if(!startSdl(&sdl))
        exit (0);
    //here the rendering function (returns a table of colors)
    // pass the tabele to draw 
    render(colors);
    
    draw(sdl.rend, colors);


    while(1)
        if(exitSdl(sdl))
            break;
    return 0;
}