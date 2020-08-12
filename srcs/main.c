/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2020/08/12 11:37:20 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/RTv1.h"

 
int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) >= 0)
    {
        ft_putendl("no error");
    }
    else
        ft_putendl("errorrrrr");

    SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
    SDL_Delay(3000);
    SDL_Quit();

    return 0;
}