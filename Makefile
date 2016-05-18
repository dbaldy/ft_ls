# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaldy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 21:59:46 by dbaldy            #+#    #+#              #
#    Updated: 2016/01/07 12:28:51 by dbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = aux.c list.c main.c lc.c ft_print_list.c analyse.c ft_print_long.c\
	  multiple_args.c multiple_args2.c print_long_aux.c device.c bonus.c\
	  bonus2.c 

BIN = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "proceeding"
	@gcc $(FLAGS) -c $(SRC)
	@make -C libft/ fclean
	@make -C libft/
	@make -C libft/ clean
	@gcc -o $(NAME) $(BIN) -L libft/ -lft
	@echo "ft_ls done"

clean:
	@/bin/rm -rf $(BIN)
	@echo "clean done"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "fclean done"

re: fclean all
