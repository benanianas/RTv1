/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/01/15 15:23:51 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

char **file_reader(char **av, char **table)
{
    int fd;
    char tmp[BUFF_SIZE + 1];
    int i;
    char *file_str;

    file_str = "\0";
    if ((fd = open(av[1], 0)))
    {
        while ((i = read(fd, tmp, BUFF_SIZE)))
        {
            tmp[i] = '\0';
            file_str = ft_strjoin(file_str, tmp);
        }
    }
    table = ft_strsplit(file_str, '\n');
    return table;
}

t_obj parser(int ac, char **av)
{
    t_obj object;
    char **table;

     
    if (ac != 2 || !(table = file_reader(av,table)) || !(table[2]))
        return (object);
    
    return (object);
}

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

int main(int ac, char **av)
{
    // t_obj object;

    // if (!(object = parser(ac,av)))
    //     perror("file ERROR :(");
    // return 0;

    t_sdl sdl;
    
    if(!startSdl(&sdl))
    {
        ft_putendl(SDL_GetError());
        exit (0);
    }
    //here the rendering function (returns a table of colors)

    // pass the tabele to draw

    
    draw(sdl.rend);

    while(1)
        if(exitSdl(sdl))
            break;
    return 0;
}