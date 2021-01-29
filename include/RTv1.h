/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:11:23 by abenani           #+#    #+#             */
/*   Updated: 2021/01/29 13:32:49 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H


# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../SDL2-2.0.12/build/include/SDL2/SDL.h"
// # include <SDL.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct s_obj
{
    int id;
    int **obj;
    struct s_obj	*next;
	struct s_obj	*head;
    
}   t_obj;

# define W_WIDTH 800
# define W_HEIGHT 500
# define BUFF_SIZE 100

typedef struct      s_sdl
{
    SDL_Window      *win;
    SDL_Renderer    *rend;
}                   t_sdl;

typedef struct      s_color
{
    int             r;
    int             g;
    int             b;
    int             a;
}                   t_color;

int                 startSdl(t_sdl *sdl);
int                 exitSdl(t_sdl sdl);
void                draw(SDL_Renderer    *rend, t_color *colors);




#endif