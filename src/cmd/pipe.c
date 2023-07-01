/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:28:55 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/25 19:48:09 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

t_pipe	init_pip(t_shell *shell, t_cmd *ptr, t_pipe p)
{
	p.i = -1;
	p.pipes = ft_count_pipe(ptr);
	shell->fd = ft_open_fd(shell, p.pipes);
	return (p);
}

void	ft_parent(t_shell *shell, t_pipe p, t_cmd *ptr)
{
	int	status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_init);
	ft_close_redir(ptr);
	if (p.i > 0)
		close(shell->fd[p.i - 1][0]);
	if (p.i < p.pipes)
		close(shell->fd[p.i][1]);
	dup2(shell->std_out, STDOUT_FILENO);
	dup2(shell->std_in, STDIN_FILENO);
	waitpid(p.pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
}

void	ft_child(t_shell *shell, t_cmd *ptr, char **env, t_pipe p)
{
	if (p.i > 0 && ft_is_builtin(ptr->prev->tab[0]))
	{
		p.fd_built = open(".字", O_RDONLY);
		dup2(p.fd_built, STDIN_FILENO);
		close (shell->fd[p.i - 1][0]);
		close(p.fd_built);
	}
	if (!ft_check_cmd(shell, ptr))
		exit(g_status);
	else
	{
		ft_redir_pipe(p.i, p.pipes, shell->fd, ptr);
		execve(ptr->tab[0], ptr->tab, env);
		ft_error(shell, CMD_ERR, p.pipes, ptr->tab[0]);
	}
}

static void	ft_norm_pipe(t_shell *shell, t_pipe p, t_cmd *ptr, char **env)
{
	p.pid = fork();
	if (p.pid < 0)
		ft_error(shell, FR_ERR, p.pipes, NULL);
	if (p.pid == 0)
		ft_child(shell, ptr, env, p);
	else
		ft_parent(shell, p, ptr);
}

t_cmd	*ft_pipe(t_shell *shell, t_cmd *ptr, char **env)
{
	static t_pipe	p;

	p = init_pip(shell, ptr, p);
	while (++p.i < (p.pipes + 1))
	{
		if (ptr && !ft_strcmp(ptr->tab[0], "exit") && (ptr->next || ptr->prev))
			ptr = ptr->next;
		ft_dup_redir(ptr);
		if (ptr && ptr->tab && (ft_strcmp(ptr->tab[0], "<<") == 0))
			ft_here_doc(shell, ptr);
		else if (ptr && ft_is_builtin(ptr->tab[0]) == 1)
			ft_pipe_built(shell, ptr, p);
		else if (ptr)
			ft_norm_pipe(shell, p, ptr, env);
		if (ptr)
			ptr = ptr->next;
	}
	unlink(".字");
	unlink(".字x");
	ft_free_fd(p.pipes, shell->fd);
	return (ptr);
}
