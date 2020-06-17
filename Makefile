# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-eng <mvan-eng@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/27 14:40:34 by mvan-eng      #+#    #+#                  #
#    Updated: 2020/05/22 14:31:33 by merlijn       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

FILES = main get_input create_hashtable memory_tools get_edges find_path \
tools edge_manipulation compare_solves list_paths find_path_edge \
queue_manipulation print_result free_queue free_solves tools_2

LIB = ft_printf/libft/libft.a ft_printf/libftprintf.a

SRC = $(FILES:%=src/%.c)

all: $(NAME)

$(NAME):
	@echo ">>>>>	$(NAME) COMPILING STARTED	<<<<<"
	@cd ft_printf && make
	@gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME)
	@echo ">>>>>	$(NAME) COMPILING SUCCESS	<<<<<"

clean:
	@echo ">>>>>	CLEANING $(NAME)	<<<<<"
	@cd ft_printf && make clean

fclean: clean
	@echo ">>>>>	REMOVING $(NAME)	<<<<<"
	@cd ft_printf && make fclean
	@rm -f $(NAME)

re: fclean
	@echo ">>>>>	$(NAME) COMPILING STARTED	<<<<<"
	@cd ft_printf && make re
	@gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME)
	@echo ">>>>>	$(NAME) COMPILING SUCCESS	<<<<<"
