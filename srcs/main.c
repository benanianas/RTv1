/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2020/11/22 12:13:43 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/RTv1.h"
#include <stdbool.h>


int randInt(int rmin, int rmax) {
    return rand() % rmax + rmin;
}


int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) >= 0)
    {
        ft_putendl("no error");
    }
    else
        ft_putendl("errorrrrr");

    SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
    

    // Initial renderer color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    bool running = true;
    SDL_Event event;
    while(running) {
        // Process events
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_KEYDOWN) {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                if(strcmp(key, "C") == 0) {
                    SDL_SetRenderDrawColor(renderer, randInt(0, 255), randInt(0, 255), randInt(0, 255), 255);
                }                    
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // Draw

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

    return 0;
}