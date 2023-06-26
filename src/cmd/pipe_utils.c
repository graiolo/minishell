/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:28:55 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/16 12:32:41 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

int	**ft_open_fd(t_shell *shell, int pipes)
{
	int		**fd;
	int		i;

	i = 0;
	fd = malloc(sizeof(int *) * (pipes));
	while (i < pipes)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
			ft_error(shell, PIPE_ERR, pipes, NULL);
		i++;
	}
	return (fd);
}

int	ft_count_pipe(t_cmd *ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		if (ptr->sep == PIPE)
			i++;
		ptr = ptr->next;
	}
	return (i);
}

void	ft_free_fd(int i, int **fd)
{
	i -= 1;
	while (i >= 0)
	{
		free(fd[i]);
		i--;
	}
	free(fd);
}

int	**ft_help_redir_pipe(int **fd, t_cmd *ptr)
{
	close(fd[0][0]);
	if (ptr->red_in != 0)
		dup2(ptr->red_in, STDIN_FILENO);
	if (ptr->red_out != 1)
		dup2(ptr->red_out, STDOUT_FILENO);
	else
		dup2(fd[0][1], STDOUT_FILENO);
	close(fd[0][1]);
	return (fd);
}

void	ft_redir_pipe(int i, int pipes, int **fd, t_cmd *ptr)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_init);
	if (i == 0)
		fd = ft_help_redir_pipe(fd, ptr);
	else
	{
		if (ptr->red_in != 0)
			dup2(ptr->red_in, STDIN_FILENO);
		else if (!ft_is_builtin(ptr->prev->tab[0]))
			dup2(fd[i - 1][0], STDIN_FILENO);
		if (i < pipes)
		{
			if (ptr->red_out != 1)
				dup2(ptr->red_out, STDOUT_FILENO);
			else
				dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][0]);
		}
		if (i == pipes)
		{
			if (ptr->red_out != 1)
				dup2(ptr->red_out, STDOUT_FILENO);
			close(fd[i - 1][0]);
		}
	}
}
