/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:28:18 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 14:33:09 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* library */

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>
# include <fcntl.h>

/* type define */

# define EMPTY 0
# define CMD 1
# define ARG 2
# define PIPE 3
# define AND 4
# define OR 5
# define COMMA 6
# define INPUT 7
# define OUTPUT 8
# define IAPPEND 9
# define OAPPEND 10
# define IOFILE 11 
# define REDIR 12
# define OWRITE 13
# define OBRACKETS 14
# define CBRACKETS 15

/* error define */

# define MALL_ERR "\e[1;31mERROR WHILE CREATING MALLOC\n\e[0m"
# define FR_ERR "\e[1;31mERROR WHILE CREATING FORK\n\e[0m"
# define PIPE_ERR "\e[1;31mERROR WHILE CREATING PIPE\n\e[0m"
# define DUP_ERR "\e[1;31mERROR WHILE CREATING DUP\n\e[0m"
# define OPEN_ERR "\e[1;31mERROR WHILE CREATING OPEN\n\e[0m"
# define CMD_ERR "command not found\n"
# define SYNTAX_ERR "syntax error\n"
# define FILE_NOT_EXE "Not executable file\n"
# define NO_FILE "No such file or directory\n"
# define NA_FILE "syntax error near unexpected token `newline'\n"
# define SYNTAX_ERR2 "syntax error near unexpected token '"
/* boolean operator */

# define TRUE 1
# define FALSE 0

/* define structs */

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**tab;
	int				red_in;
	int				red_out;
	int				type;
	int				sep;
	int				pipe;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_shell
{
	t_token	*token;
	t_cmd	*cmd;
	char	**env;
	char	*path;
	int		status;
	int		std_in;
	int		std_out;
	int		**fd;
}	t_shell;

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		outfile;
	int		infile;
	char	**cmd_args;
}	t_pipex;

typedef struct s_card
{
	char	**card;
	int		*typo;
}	t_card;

typedef struct s_list_token
{
	t_token	*token_rmv;
	t_token	*token_list;
	t_token	**token;
	t_token	*tmp;
}	t_list_token;

typedef struct s_pipe
{
	pid_t	pid;
	int		pipes;
	int		i;
	int		fd_built;
	int		fd_built_in;
}	t_pipe;

extern int	g_status;

/* file: error.c */

char	*ft_error_line(char *name, char *value, char *error);

/* file: quotes.c */

int		ft_quotes(char *str, int len);
int		ft_is_sep(char *line, int i);
char	*ft_line_space(char *str);
int		ft_slash(char *str, int len);
char	*ft_correct_form(char *line);

/* file: brackets.c */

int		ft_brackets(char *str, int len);

/*  file: shell_split.c */

char	**ft_shell_split(char *s, char c);

/* file: operator.c */

void	ft_operator(t_shell *shell, t_token *token);

/* file: token.c */

void	ft_get_token(t_shell *shell, char *str);
void	ft_clean_type(t_shell *shell, t_token *token);
void	ft_clean_cmd(t_shell *shell, char **cmd);
void	ft_clean_arg(t_shell *shell, char **str);

/* file: list.c */

void	*ft_add_back(t_token **head, char *line);
void	ft_add_node(t_token **head, t_token *start, char *str);
void	ft_remove_head(t_token **head);
void	ft_remove_node(t_token **head, t_token *node);
t_token	*ft_new_node(char *str, int typo);
void	ft_free_list(t_token **head);

/* file: list_utils.c */

void	ft_join_list(t_token **cmd, t_token **red, t_token **new);
void	ft_update_prev(t_token *token);
void	ft_printf_list(t_token *token);

/*file expansion.c */

void	*ft_expand(t_shell *shell, char *str);
char	*ft_get_env_varible(t_shell *shell, char *str, int *i);

/* file: types.c */

void	ft_type_arg(t_token *token);
int		ft_is_type(t_token *token, int type);
int		ft_is_types(t_token *token, char *types);

/* file: read_token.c */

t_token	*ft_read_cmd(t_shell *shell, t_token *tok);
void	ft_read_tok(t_shell *shell);
t_cmd	*ft_add_cmd_back(t_shell *shell, t_cmd **head, char **line, t_token *t);
t_cmd	*ft_add_cmd_help(t_shell *shell, char **tab, int i);
t_token	*ft_norm_fist(t_shell *shell, t_token *tok, char ***args);

/* file: getenv.c */

char	*ft_getenv(t_shell *shell, const char *var);

/* file: cmd_tab.c */

char	*ft_get_path_cmd(t_shell *shell, char *cmd);
int		ft_is_cmd(t_token *tok);
int		ft_cmd_sep(t_cmd *cmd, t_token *tok);
char	**ft_cmdmat(t_shell *shell, t_token *n_tok, char *cmd);
void	ft_free_cmd(t_cmd	**head);

/* file: exit.c */

void	ft_free_shell(t_shell *shell);
void	ft_error(t_shell *shell, char *str, int i, char *value);
void	ft_free_exit(t_shell *shell);
void	ft_error_noc(t_shell *shell, char *str, char *value);
int		ft_check_cmd(t_shell *shell, t_cmd *cmd);

/* file: redir.c */

char	**ft_get_env(char **env);
int		ft_check_redir(t_token *tok);
t_cmd	*ft_redir_in(t_token *tok, t_cmd *cmd);
void	ft_dup_redir(t_cmd *cmd);
void	ft_close_redir(t_cmd *cmd);
t_cmd	*ft_redir_cmd(t_cmd *cmd);

/* file: move_token.c */

t_token	*ft_prev_sep(t_token *tok);
t_token	*ft_next_sep(t_token *tok);
int		ft_tok_tobreak(t_token *tok, char *direction);

/* file exec.c */

void	ft_init_cmd(t_cmd *new);
void	ft_simple_cmd(t_shell *shell, t_cmd *cmd, char **env);
void	ft_exec(t_shell *shell, t_cmd *ptr);

/* file bool.c */

t_cmd	*ft_and(t_shell *shell, t_cmd *ptr, char **env);
t_cmd	*ft_or(t_shell *shell, t_cmd *cmd, char **env);

/* file: pipe.c */

void	ft_sig_partent(t_cmd *ptr);
t_cmd	*ft_pipe(t_shell *shell, t_cmd *ptr, char **env);

/* file: pipe_utils.c */

int		**ft_open_fd(t_shell *shell, int pipes);
int		ft_count_pipe(t_cmd *ptr);
void	ft_free_fd(int i, int **fd);
int		**ft_help_redir_pipe(int **fd, t_cmd *ptr);
void	ft_redir_pipe(int i, int pipes, int **fd, t_cmd *ptr);

/* file: wildcard.c */

void	ft_wildcard(t_shell *shell, t_token **token);

/* file: wildcard_utils.c */

int		ft_sub_str(char *str, char *sub);
int		ft_right_compare(char *files, char *card);
int		ft_left_compare(char *files, char *card);

/* file: wildcard_second_utils.c */

char	**ft_card(t_shell *shell, char *str);
char	*ft_rm_asterix(char *str);

/* file: wildcard_third_utils.c */

void	ft_correct_file(char **files, t_card cards, char **new);
char	**ft_get_name_files(char *file);

/* file: builtin.c */

int		ft_is_builtin(char *str);
int		ft_builtin(t_shell *shell, char **tab);
void	ft_pipe_built(t_shell *shell, t_cmd *ptr, t_pipe p);

/* file: signal.c */

void	ft_sig_init(int sign);
void	ft_sig_term(t_shell *shell);

/* file: history.c */

void	ft_clear_history(t_shell *shell);
void	ft_add_history(t_shell *shell, char *line);

/* file: read_line.c */

char	*ft_read_line(int argc, char **argv, t_shell *shell);

/* file: here_doc.c */
char	**ft_here_cmd(t_token *tok);
void	ft_here_doc(t_shell *shell, t_cmd *cmd);

/* file: cmd_prio.c */

void	ft_prio(t_shell *shell);

/* file: cmd_prio_relist.c */

void	ft_extract_sub_list(t_token **list,
			t_token *start, t_token *stop);

/* -------------------------------- */

void	ft_pwd(void);
void	ft_cd(t_shell *shell, char **path);
void	ft_echo(t_shell *shell, char **str);
void	ft_exit(t_shell *shell, char **status);
void	ft_env(t_shell *shell, char **arg);
void	ft_export(t_shell *shell, char **new);
char	**ft_sort_env(char **env);
void	ft_unset(t_shell *shell, char **del);
void	ft_read(t_shell *shell, char **new);

#endif
