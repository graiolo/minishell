# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: graiolo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 16:19:35 by graiolo           #+#    #+#              #
#    Updated: 2023/06/20 11:14:19 by graiolo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = new_libft

all: $(NAME)

$(NAME):
	make -C libft
	make -C ft_printf
	make -C get_next_line

clean:
	make -C libft clean
	make -C ft_printf clean
	make -C get_next_line clean

fclean: clean
	make -C libft fclean
	make -C ft_printf fclean
	make -C get_next_line fclean

bonus:
	make -C libft bonus
	make -C ft_printf bonus
	make -C get_next_line bonus

re : fclean all

.PHONY: all clean fclean



