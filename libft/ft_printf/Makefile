# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: graiolo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 16:38:22 by graiolo           #+#    #+#              #
#    Updated: 2023/06/20 16:22:42 by graiolo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	 ../archive/libft.a

CC		=	 gcc $(CFLAGS)

CFLAGS		=	 -Wall -Werror -Wextra -c -I $(IDIR)

IDIR		=	 ../include

RM		=	 rm -f

LIB		=	 ar rcs $(NAME)

ODIR		=	 obj/

ODIR_BONUS	=	 obj_bonus/

DIR		=	 src/

DIR_BONUS	=	 src_bonus/

SRC_FILES	=	ft_print_hex.c ft_print_ptr.c\
			ft_print_unsigned.c ft_printf_utils.c\
			ft_printf.c\

SRC_FILES_BONUS	=	ft_printf.c ft_printf_utils.c ft_print_ptr.c ft_print_unsigned.c ft_print_hex.c\
				ft_printf_flags.c ft_printf_char.c ft_printf_length_flag.c ft_printf_print_num.c\
				ft_hex_unsigned_support.c ft_num_support.c

OBJ_BONUS 	=	 $(SRC_FILES_BONUS:.c=.o)

OBJ	 	=	 $(SRC_FILES:.c=.o)

$(ODIR_BONUS)%.o : $(DIR_BONUS)%.c
	@printf "\033[0;33mpCompiling: %s\n"  $$(basename "$@" .o)
	@$(CC) $(CFLAG) $< -o $@

$(ODIR)%.o : $(DIR)%.c
	@printf "\033[0;33mCompiling: %s\n"  $$(basename "$@" .o)
	@$(CC) $(CFLAG) $< -o $@

OFILE_BONUS	=	 $(addprefix $(ODIR_BONUS), $(OBJ_BONUS))

OFILE		=	 $(addprefix $(ODIR), $(OBJ))


DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
RED = \033[0;91m
CIANO = \033[0;96m

$(NAME):	$(OFILE) 
			@$(LIB) $(OFILE)

all:		$(NAME)

clean:
			@$(RM) $(OFILE) $(OFILE_BONUS)
			@echo "$(CIANO)file .obj di printf eliminati con successo!$(DEF_COLOR)"

clean2:
			@$(RM) $(OFILE) $(OFILE_BONUS)


fclean:		clean2
			@$(RM) libft.a
			@echo "$(RED)printf.a rimossa con successo!$(DEF_COLOR)"	

re:			fclean all

bonus:		$(OFILE) $(OFILE_BONUS) 
			@$(LIB) $(OFILE) $(OFILE_BONUS)
			@echo "$(GREEN)bonus printf.a compilata con successo!$(DEF_COLOR)"

.PHONY:		all clean fclean re
