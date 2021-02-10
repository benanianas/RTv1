# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenani <abenani@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/11 10:39:21 by abenani           #+#    #+#              #
#    Updated: 2021/02/09 13:20:49 by abenani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SDLSRC = SDL2-2.0.12.tar.gz
HDR_F = ../include/RTv1.h
SDL = SDL2-2.0.12
SDLB = $(SDL)/build
C_SDL = `$(SDLB)/sdl2-config --cflags --libs`
LIBFTD = libft
SRC_D = srcs



SRC_F = main.c sdltools.c vecs.c rendertools.c parser1.c parsercamlight.c
SRC = $(addprefix srcs/, $(SRC_F))
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME):$(SDL) $(OBJ)
		 @$(MAKE) -C $(LIBFTD)
		 $(CC) $(OBJ) $(LIBFT) $(C_SDL) -o $@ -lm

$(SDL):
		tar -xf $(SDLSRC) && mkdir $(SDLB)
		cd $(SDLB) && ../configure --prefix=$(shell pwd)/$(SDLB)
		$(MAKE) -C $(SDLB)
		$(MAKE) -C $(SDLB) install

$(SRC_D)/%.o: $(SRC_D)%.c
		$(CC) $(CFLAGS) -c $< -o $@
clean:
		rm -f $(OBJ)
		@$(MAKE) -C $(LIBFTD) clean
		
fclean: clean
		@$(MAKE) -C $(LIBFTD) fclean
		rm -f $(NAME)
		rm -rf $(SDL)
