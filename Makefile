# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/11 10:39:21 by abenani           #+#    #+#              #
#    Updated: 2020/08/12 11:37:17 by abenani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
C_SDL = `$(SDL_B)/sdl2-config --cflags --libs`
LIBFT_D = libft
SDLSRC = SDL2-2.0.12.tar.gz
SDL_N = SDL2-2.0.12
SDL = SDL
SDL_B = $(SDL)/build



SRC_F = main.c 
SRC = $(addprefix srcs/, $(SRC_F))
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(SDL) $(OBJ) 
		$(MAKE) -C $(LIBFT_D)
		$(CC) $(SRC) $(LIBFT) $(C_SDL) -o $(NAME)

$(SDL):
		tar -xf $(SDLSRC)
		mv $(SDL_N) $(SDL)
		mkdir $(SDL_B)
		cd $(SDL_B) && ../configure
		$(MAKE) -C $(SDL_B)
		sudo $(MAKE) -C $(SDL_B) install
		
		
clean:
		rm $(OBJ)
		$(MAKE) -C $(LIBFT_D) clean
		
fclean: clean
		$(MAKE) -C $(LIBFT_D) fclean
		rm -rf $(SDL)
		rm -f $(NAME)

