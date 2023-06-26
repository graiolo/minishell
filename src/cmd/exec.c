/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:43:06 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/17 02:51:47 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_init_cmd(t_cmd *new)
{
	new->tab = NULL;
	new->red_in = 0;
	new->red_out = 1;
	new->type = 0;
	new->sep = 0;
	new->pipe = 0;
	new->next = NULL;
	new->prev = NULL;
}

void	ft_child_parent(t_shell *shell, t_cmd *cmd, pid_t pid, char **env)
{
	int	status;

	if (pid < 0)
		ft_error(shell, FR_ERR, 0, NULL);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_sig_init);
		if (cmd->red_in != 0 || cmd->red_out != 1)
			ft_dup_redir(cmd);
		execve(cmd->tab[0], cmd->tab, env);
		ft_error(shell, CMD_ERR, 0, cmd->tab[0]);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_sig_init);
		if (cmd->red_in != 0 || cmd->red_out != 1)
			ft_close_redir(cmd);
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_status = WTERMSIG(status) + 128;
	}
}

void	ft_simple_cmd(t_shell *shell, t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		stdout;

	stdout = dup(STDOUT_FILENO);
	if (!ft_check_cmd(shell, cmd))
		return ;
	if (cmd->tab && ft_strcmp(cmd->tab[0], "<<") == 0)
		ft_here_doc(shell, cmd);
	else if (cmd->tab && ft_is_builtin(cmd->tab[0]))
	{
		if (cmd->red_in != 0 || cmd->red_out != 1)
			ft_dup_redir(cmd);
		ft_builtin(shell, cmd->tab);
		if (cmd->red_in != 0 || cmd->red_out != 1)
			ft_close_redir(cmd);
		dup2(stdout, STDOUT_FILENO);
		close(stdout);
	}
	else if (cmd->tab)
	{
		pid = fork();
		ft_child_parent(shell, cmd, pid, env);
	}
}

void	ft_exec(t_shell *shell, t_cmd *ptr)
{
	if (ptr != NULL)
	{
		if (ptr->tab && !ft_strcmp(ptr->tab[0], "exit")
			&& (ptr->next || ptr->prev))
			ptr = ptr->next;
		if (ptr && ptr->next == NULL)
			ft_simple_cmd(shell, ptr, shell->env);
		else if (ptr && ptr->sep == PIPE)
			ptr = ft_pipe(shell, ptr, shell->env);
		else if (ptr && ptr->sep == OR)
			ptr = ft_or(shell, ptr, shell->env);
		else if (ptr && ptr->sep == AND)
			ptr = ft_and(shell, ptr, shell->env);
		else if (ptr)
			ft_simple_cmd(shell, ptr, shell->env);
		if (ptr != NULL)
			ft_exec(shell, ptr->next);
	}
	ft_free_shell(shell);
	return ;
}
