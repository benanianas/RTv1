/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/02/02 11:38:54 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"


int main(int ac, char **av)
{
    // t_sdl sdl;
    // t_color *img_buff;
    // img_buff = malloc(W_WIDTH * W_HEIGHT * sizeof(t_color));
   
    // if(!startSdl(&sdl))
    //     exit (0);
    // render(img_buff);
    // draw(sdl.rend, img_buff);
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
    from.z = 1;
    
    t_vec to;
    to.x = 1;
    to.y = 0;
    to.z = 1;

    t_cam vecs = cam_mx(from, to);

    t_vec new = camera_transform(vecs, point, from);

    printf("(%f,%f,%f)\n", new.x, new.y, new.z);
    
    
    return 0;
}