/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:11:23 by abenani           #+#    #+#             */
/*   Updated: 2021/02/10 13:07:42 by abenani          ###   ########.fr       */
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

# define W_WIDTH 800
# define W_HEIGHT 500
# define BUFF_SIZE 100

typedef struct      s_obj
{
    int             id;
    int             oneint;
    int             **obj;
    struct s_obj	*next;
	struct s_obj	*head;
    
}                   t_obj;

typedef struct      s_vec
{
    double          x;
    double          y;
    double          z;
}                   t_vec;

typedef struct      s_sdl
{
    SDL_Window      *win;
    SDL_Renderer    *rend;
}                   t_sdl;

typedef struct      s_cam
{
    t_vec           f;
    t_vec           r;
    t_vec           u;
    t_vec           pos;
}                   t_cam;

typedef struct      s_color
{
    int             r;
    int             g;
    int             b;
    int             a;
}                   t_color;

typedef struct      s_sphere
{
    t_vec           center;
    t_vec           x;
    int             rad;
    double          t;
    double          tmp;
    
}                   t_sphere;

typedef struct      s_eq
{
    double          a;
    double          b;
    double          c;
    double          delta;
}                   t_eq;


int                 startSdl(t_sdl *sdl);
int                 exitSdl(t_sdl sdl);
void                draw(SDL_Renderer    *rend, t_color *colors);


t_vec               vec(double x, double y, double z);
double              vec_dot(t_vec a, t_vec b);
t_vec               vec_cross(t_vec a, t_vec b);
double              vec_magnitude(t_vec vec);
t_vec               vec_unit(t_vec vec);
t_vec               vec_add(t_vec a, t_vec b);
t_vec               vec_num(t_vec vec, double num);
t_vec               vec_sub(t_vec a, t_vec b);


void                render(t_color *colors, t_obj *object);
t_cam               cam_mx(t_vec from, t_vec to);
t_vec               camera_transform(t_cam cam, t_vec old_p);
t_vec               objvec(int *arr);
t_color             objcolor(int *arr);
void                renderer_loop(t_color *img_buff, t_obj *obj, t_cam cam);

int                 check_cam(char *tab, t_obj *obj);
int                 check_light(char *tab, t_obj *obj);
void                delet_table(char **tab);
char                **nocomment(char **table);
char                **nospace_nocomment(char **table);
char                **file_reader(char **av, char **table);
int                 parser(int ac, char **av, t_obj *object);
int                 arr_counter(char **arr);
void                node_filler(int id, int *object, int objnum, int add, t_obj *obj);
void                first_node(t_obj *obj, int *object, int objnum);
int                 check_sphere(char *tab, t_obj *obj);
int                 check_plane(char *tab, t_obj *obj);
int                 check_cone(char *tab, t_obj *obj);
int                 check_cy(char *tab, t_obj *obj);








#endif