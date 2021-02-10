/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/02/10 12:40:55 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"


int main(int argc, char **argv)
{

    t_obj *object;  
    t_sdl sdl;
    t_color *img_buff;

    object = (t_obj *)malloc(sizeof(t_obj));
    if (!parser(argc, argv, object))
    {
        perror("file ERROR :(");
        exit (0); 
    }
    img_buff = malloc(W_WIDTH * W_HEIGHT * sizeof(t_color));
    if(!startSdl(&sdl))
        exit (0);   
    render(img_buff, object);
    draw(sdl.rend, img_buff);
    while(1)
        if(exitSdl(sdl))
            break;
    return 0;
}