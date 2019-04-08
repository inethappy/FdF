# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/08 12:39:39 by mkotytsk          #+#    #+#              #
#    Updated: 2019/04/08 12:39:41 by mkotytsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror

SOURCES_DIR	:= ./src/
OBJECTS_DIR	:= ./obj/
INCLUDE_DIR	:= ./inc/
LIB_DIR		:= ./lib/
SOURCES		:=	main.c \
				save_input.c \
				put_img.c \
				diff_plans.c \
				deal_keys.c \
				moving.c \
				brezenhame.c
OBJECTS		:= $(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	:= $(LIB_DIR)libft
LIBFT_INC	:= $(LIBFT_DIR)
LIBFT_FL	:= -lft -L $(LIBFT_DIR)
PRINTF_FL	:= $(LIB_DIR)ft_printf/libftprintf.a
PRINTF_INC	:= $(LIB_DIR)ft_printf

LIB_FLAGS	:= $(LIBFT_FL) $(PRINTF_FL)

HEADER_FLAGS	:= -I $(INCLUDE_DIR) -I $(LIBFT_INC) -I $(PRINTF_INC)

FRAM = -L minilibx -I minilibx -lmlx -framework OpenGL -framework AppKit

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
		$(CC) $(OBJECTS) $(LIB_FLAGS) -o $(NAME) $(FRAM)

$(OBJECTS): | $(OBJECTS_DIR)

$(OBJECTS_DIR):
		mkdir $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o: %.c
		$(CC)  -c $< -o $@ $(HEADER_FLAGS)

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJECTS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJECTS_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

vpath %.c $(SOURCES_DIR)
