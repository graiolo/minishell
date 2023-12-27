/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:23:07 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 18:12:23 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* entro
primo figlio con input nullo output in .file_st
secondo figlio con input /etc/passwd .file_sc
get_next_line(.file_st) && get_next_line(.file_sc)
se non ci sono differenze allora lista ad alta priorita, altrimenti nope

prendo tutto quello che est prima del comnodeo ad alta priorita (compreso tra
il null, ||, && "()") e lo butto in una lista
tutto questo lo metto subito dopo tutto quello che segue il processo ad alta
priorita e quindi lo butto prima di null, ||, && "()"
    e tra il vecchio comnodeo e il nuovo ci appioppo un && 
il vecchio comnodeo ha output non nel pipe ma in /dev/null
FINE.

N.B il cat a bassa priorita diventa read */

#include "./../../include/minishell.h"

static void	first_child(t_shell *shell, t_pipex pipex, char *argv)
{
	char	*path;

	(void)argv;
	dup2(pipex.infile, 0);
	dup2(pipex.outfile, 1);
	dup2(pipex.outfile, 2);
	path = ft_get_path_cmd(shell, argv);
	pipex.cmd_args = ft_split(path, ' ');
	execve(path, pipex.cmd_args, NULL);
	ft_free_mat(pipex.cmd_args);
	free(path);
	ft_error(shell, NULL, 0, NULL);
}

static void	ft_norm_is_prio(t_shell *shell, char *cmd,
	t_pipex	pipex, char	**files[2])
{
	pipex.infile = open("/dev/null", O_RDONLY);
	pipex.outfile = open(".入", O_TRUNC | O_CREAT | O_RDWR, 0644);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(shell, pipex, cmd);
	waitpid(pipex.pid1, NULL, 0);
	close(pipex.infile);
	close(pipex.outfile);
	pipex.infile = open("/etc/passwd", O_RDONLY);
	pipex.outfile = open(".又", O_TRUNC | O_CREAT | O_RDWR, 0644);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(shell, pipex, cmd);
	waitpid(pipex.pid1, NULL, 0);
	close(pipex.infile);
	close(pipex.outfile);
	files[1] = ft_get_name_files(".又");
	files[0] = ft_get_name_files(".入");
}

static int	ft_is_prio(t_shell *shell, char *cmd)
{
	t_pipex	pipex;
	int		i;
	char	**files[2];

	i = 0;
	files[0] = NULL;
	files[1] = NULL;
	pipex.infile = 0;
	pipex.outfile = 0;
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "vi") || !ft_strcmp(cmd, "vim"))
		return (0);
	ft_norm_is_prio(shell, cmd, pipex, files);
	unlink(".入");
	unlink(".又");
	while (files[0][i] != NULL && files[1][i] != NULL
		&& ft_strcmp(files[0][i], files[1][i]) == 0)
		i++;
	i = ft_strcmp(files[0][i], files[1][i]);
	ft_free_mat(files[0]);
	ft_free_mat(files[1]);
	return (i);
}

void	ft_prio(t_shell *shell)
{
	t_token	*token;
	t_token	*start;

	token = shell->token;
	start = token;
	if (ft_is_types(token, "TPERCL") == 1)
		return ;
	while (token != NULL)
	{
		if (ft_is_types(token, "CRELB") == 1)
			start = token->next;
		if ((token->type == CMD && ft_is_prio(shell, token->str) == 0)
			|| (token->type == CMD && ft_is_prio(shell, token->str) != 0
				&& token->next != NULL && token->next->type != PIPE))
		{
			ft_extract_sub_list(&shell->token, start, token);
			return ;
		}
		token = token->next;
	}
}
