/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdltools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:13:01 by abenani           #+#    #+#             */
/*   Updated: 2021/01/15 18:41:19 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

int    startSdl(t_sdl *sdl)
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        if((sdl->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN)))
            if((sdl->rend = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE)))
                return 1;
            else
                SDL_DestroyWindow(sdl->win);
    }
        else
           SDL_Quit();
    return 0;
}

int exitSdl(t_sdl sdl)
{
    SDL_Event e;
    
    if(SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
        {
            SDL_DestroyRenderer(sdl.rend);
            SDL_DestroyWindow(sdl.win);
            SDL_Quit();
            return 1;
        }
    }
    return 0;
}


void draw(SDL_Renderer    *rend)
{
    // SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rend, 255, 0, 255, 255);
    int i = 0;
    while (i < W_HEIGHT)
    {
        int j = 0;
        while(j < W_WIDTH)
        {
            SDL_RenderDrawPoint(rend, j, i);
            j++;
        }
        i++;
    }
    SDL_RenderPresent(rend);
}
