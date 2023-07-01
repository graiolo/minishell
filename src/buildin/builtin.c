/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:07:22 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/23 11:15:16 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

int	ft_is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(str, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(str, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(str, "export") == 0)
		return (TRUE);
	if (ft_strcmp(str, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(str, "env") == 0)
		return (TRUE);
	if (ft_strcmp(str, "exit") == 0)
		return (TRUE);
	if (ft_strcmp(str, "read") == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_builtin(t_shell *shell, char **tab)
{
	if (ft_strcmp(tab[0], "echo") == 0)
		ft_echo(shell, tab);
	else if (ft_strcmp(tab[0], "cd") == 0)
		ft_cd(shell, tab);
	else if (ft_strcmp(tab[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tab[0], "export") == 0)
		ft_export(shell, tab);
	else if (ft_strcmp(tab[0], "unset") == 0)
		ft_unset(shell, tab);
	else if (ft_strcmp(tab[0], "env") == 0)
		ft_env(shell, tab);
	else if (ft_strcmp(tab[0], "exit") == 0)
		ft_exit(shell, tab);
	else if (ft_strcmp(tab[0], "read") == 0)
		ft_read(shell, tab);
	return (FALSE);
}

void	ft_pipe_built(t_shell *shell, t_cmd *ptr, t_pipe p)
{
	p.fd_built = open(".字", O_RDWR | O_CREAT | O_TRUNC, 0644);
	p.fd_built_in = open(".字x", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p.i > 0)
		close (shell->fd[p.i - 1][0]);
	if (ptr->red_in != 0)
		dup2(ptr->red_in, STDIN_FILENO);
	if (ptr && ptr->next && ptr->next->red_in == 0)
		ptr->next->red_in = p.fd_built;
	if (ptr->red_out != 1)
		dup2(ptr->red_out, STDOUT_FILENO);
	else if (p.i != p.pipes)
		dup2(p.fd_built, STDOUT_FILENO);
	if (p.i != p.pipes)
		close (shell->fd[p.i][1]);
	ft_builtin(shell, ptr->tab);
	if (ptr->red_in != 0 || ptr->red_out != 1)
		ft_close_redir(ptr);
	dup2(shell->std_out, STDOUT_FILENO);
	dup2(shell->std_in, STDIN_FILENO);
	close(p.fd_built);
	close(p.fd_built_in);
}
