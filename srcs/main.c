/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2020/12/23 18:25:26 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/RTv1.h"


int main(int argc, char **argv)
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    int             running;
    
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, 400, 300);
    SDL_RenderPresent(renderer);
    
    running = 1;
    while(running)
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) {
                running = 0;
            }
            // ft_putchar(event.key.keysym.sym);
            // ft_putstr(" : ");
            // ft_putstr(SDL_GetKeyName(event.key.keysym.sym));
            // ft_putendl("  ");
        }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}