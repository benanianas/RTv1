/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/01/25 12:57:24 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void render()
{
    float i;
    float j;

    float width = 2;
    float height = 2;
    int pixels = 2;
      
    float num = pixels * 2;
    /*
    num changes
    2 ->  1 pixel
    8 -> 4 pixels
    16 -> 8 pixels
    */
    
    j = 1/num;
    while (j < height)
    {
        i = 1/num;
        while(i < width)
        {
            float x = (2*(i/width)-1)*(width/height);
            float y = 1-2*(j/height);
            printf("[%.4f , %.4f] ", i, j);
            i+=2/num;
        }
        printf("***\n");
        j+=2/num;
    }
    // printf("***%.4f***\n", (width/height));
}

int main(int ac, char **av)
{
    t_sdl sdl;
   
    // if(!startSdl(&sdl))
    //     exit (0);
    //here the rendering function (returns a table of colors)
    // pass the tabele to draw
    render();
    // draw(sdl.rend);

    // while(1)
    //     if(exitSdl(sdl))
    //         break;
    return 0;
}