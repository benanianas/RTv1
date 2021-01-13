/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/01/13 19:00:39 by abenani          ###   ########.fr       */
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

int main(int ac, char **av)
{
    // t_obj object;

    // if (!(object = parser(ac,av)))
    //     perror("file ERROR :(");
    // return 0;

    t_sdl sdl;
    
    SDL_Init(SDL_INIT_VIDEO);
    sdl.win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_OPENGL);
    sdl.rend = SDL_CreateRenderer(sdl.win, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC);

     SDL_SetRenderDrawColor(sdl.rend, 0, 255, 0, 255);
     SDL_RenderDrawPoint(sdl.rend, 0, 0);
    SDL_RenderPresent(sdl.rend);
    
    while(1)
        if(exitSdl(sdl))
            break;
    return 0;
}