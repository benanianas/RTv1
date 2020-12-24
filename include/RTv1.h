/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:11:23 by abenani           #+#    #+#             */
/*   Updated: 2020/12/24 16:20:05 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H


# include <stdlib.h>
# include <stdio.h>
#include <fcntl.h>
# include <SDL.h>
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
# define W_HEIGHT 600
# define BUFF_SIZE 100


#endif