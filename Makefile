# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenani <abenani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/11 10:39:21 by abenani           #+#    #+#              #
#    Updated: 2020/11/22 12:18:14 by abenani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
C_SDL = `sdl2-config --cflags --libs`
LIBFT_D = libft


SRC_F = main.c 
SRC = $(addprefix srcs/, $(SRC_F))
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(SDL)
		$(MAKE) -C $(LIBFT_D)
		$(CC) $(SRC) $(LIBFT) $(C_SDL) -o $(NAME)		
		
clean:
		# rm $(OBJ)
		$(MAKE) -C $(LIBFT_D) clean
		
fclean: clean
		$(MAKE) -C $(LIBFT_D) fclean
		rm -f $(NAME)

