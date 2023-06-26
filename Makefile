NAME	= minishell

CC		= cc 

CFLAGS	= -Wall -Werror -Wextra -g
SRC		= 	./src/main.c\
			./src/cmd/exec.c\
			./src/reader/move_token.c\
			./src/reader/read_token.c\
			./src/reader/read_cmd.c\
			./src/cmd/pipe.c\
			./src/cmd/pipe_utils.c\
			./src/cmd/bool.c\
			./src/cmd/getenv.c\
			./src/redir/redir.c\
			./src/redir/here_doc.c\
			./src/utils/exit.c\
			./src/cmd/cmd_tab.c\
			./src/parsing/quotes.c ./src/parsing/quotes_utils.c\
			./src/parsing/brackets.c\
			./src/extra/list.c ./src/extra/list_utils.c\
			./src/extra/read_line.c\
			./src/extra/error.c\
			./src/parsing/shell_split.c\
			./src/parsing/operator.c\
			./src/parsing/expansion.c\
			./src/parsing/types.c\
			./src/parsing/token.c ./src/parsing/token_clean.c\
			./src/parsing/wildcard.c\
			./src/parsing/wildcard_utils.c\
			./src/parsing/wildcard_second_utils.c\
			./src/parsing/wildcard_third_utils.c\
			./src/prio/cmd_prio.c ./src/prio/cmd_prio_relist.c\
			./src/buildin/builtin.c\
			./src/buildin/pwd.c\
			./src/buildin/echo.c\
			./src/buildin/cd.c\
			./src/buildin/exit.c\
			./src/buildin/env.c\
			./src/buildin/export.c ./src/buildin/export_sort.c\
			./src/buildin/read.c\
			./src/buildin/unset.c\
			./src/signal/signal.c\
			./src/utils/history.c\

LIB		= ./libft/archive/libft.a

OBJ		= $(SRC:.c=.o)

%.o: %.c
	@printf "$(YELLO)Compiling: %s\n" $$(basename "$@" .o)
	@$(CC) $(CFLAGS) -I ./include/ -c $< -o $@

DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
RED = \033[0;91m
CIANO = \033[0;96m
YELLO = \033[0;33m
PURPLE = \033[0;35m

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC ./libft 
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME) $(LIB)
	@printf "$(PURPLE)minishell ready assai\n$(DEF_COLOR)" 

clean:
	@make -sC ./libft clean 
	@rm -rf $(OBJ)
	@echo "$(CIANO)file .obj di $(NAME) eliminati con successo!$(DEF_COLOR)"

fclean:
	@rm -rf $(OBJ)
	@echo "$(CIANO)file .obj di $(NAME) eliminati con successo!$(DEF_COLOR)"
	@make -sC ./libft fclean
	@echo "$(RED)$(NAME) rimossa con successo!$(DEF_COLOR)"
	@rm -f $(NAME)

bonus: $(NAME)

cmp:
	@make -sC ./libft

re: fclean all 

.PHONY: all clean fclean bonus re 
