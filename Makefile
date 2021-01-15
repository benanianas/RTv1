# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/11 10:39:21 by abenani           #+#    #+#              #
#    Updated: 2021/01/15 18:45:50 by abenani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
SDLSRC = SDL2-2.0.12.tar.gz
HDR = include/RTv1.h
SDL = SDL2-2.0.12
SDLB = $(SDL)/build
C_SDL = `$(SDLB)/sdl2-config --cflags --libs`
LIBFTD = libft
SRC_D = srcs



SRC_F = main.c sdltools.c
SRC = $(addprefix srcs/, $(SRC_F))
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME):$(SDL) $(OBJ)
		 @$(MAKE) -C $(LIBFTD)
		 $(CC) $(OBJ) $(LIBFT) $(C_SDL) -o $@		

$(SDL):
		tar -xf $(SDLSRC) && mkdir $(SDLB)
		cd $(SDLB) && ../configure --prefix=$(shell pwd)/$(SDLB)
		$(MAKE) -C $(SDLB)
		$(MAKE) -C $(SDLB) install

$(SRC_D)/%.o: %.c
		$(CC) -I $(SDLB)/include/SDL2 -c -o $< $@
clean:
		rm -f $(OBJ)
		@$(MAKE) -C $(LIBFTD) clean
		
fclean: clean
		@@$(MAKE) -C $(LIBFTD) fclean
		rm -f $(NAME)
		rm -rf $(SDL)

