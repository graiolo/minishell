/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:20:19 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 15:59:18 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_add_history(t_shell *shell, char *line)
{
	int		fd;
	char	*f_history;

	if (ft_getenv(shell, "HOME") == NULL)
		return ;
	f_history = ft_strjoin(ft_getenv(shell, "HOME"), "/.minishell_history");
	fd = open(f_history, O_CREAT | O_APPEND | O_WRONLY, 0644);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(f_history);
	close(fd);
}

void	ft_clear_history(t_shell *shell)
{
	char	*f_history;

	f_history = NULL;
	if (ft_getenv(shell, "HOME") != NULL)
		f_history = ft_strjoin(ft_getenv(shell, "HOME"), "/.minishell_history");
	if (ft_getenv(shell, "HOME") != NULL)
		unlink((const char *)f_history);
	free(f_history);
}
