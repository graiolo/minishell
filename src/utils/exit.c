/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:26:02 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/23 11:11:53 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_free_shell(t_shell *shell)
{
	if (shell != NULL)
	{
		if (shell->token != NULL)
			ft_free_list(&(shell->token));
		if (shell->cmd != NULL)
			ft_free_cmd(&(shell->cmd));
	}
}

int	ft_check_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->red_in == -1)
	{
		ft_error_noc(shell, NA_FILE, NULL);
		return (0);
	}
	if (cmd->tab && cmd->tab[0] == NULL)
	{
		ft_error_noc(shell, CMD_ERR, NULL);
		return (0);
	}
	if (cmd->tab && ft_strncmp(cmd->tab[0], "./", 2) == 0)
	{
		if (access(cmd->tab[0], F_OK) == -1)
			ft_error_noc(shell, CMD_ERR, cmd->tab[0]);
		else if (access(cmd->tab[0], X_OK) == -1)
			ft_error_noc(shell, FILE_NOT_EXE, cmd->tab[0]);
		return (0);
	}
	return (1);
}

void	ft_error(t_shell *shell, char *str, int i, char *value)
{
	char	*err;

	err = ft_error_line("bash: ", value, str);
	ft_free_mat(shell->env);
	if (i != 0)
		ft_free_fd(i, shell->fd);
	ft_free_shell(shell);
	free(shell);
	ft_putstr_fd(err, STDERR_FILENO);
	free(err);
	if (!ft_strcmp(CMD_ERR, str))
		g_status = 127;
	else if (!ft_strcmp(MALL_ERR, str) || !ft_strcmp(SYNTAX_ERR2, str))
		g_status = 2;
	else if (!ft_strcmp(OPEN_ERR, str))
		g_status = 1;
	else if (!ft_strcmp(NO_FILE, str) || !ft_strcmp(SYNTAX_ERR, str))
		g_status = 1;
	exit(g_status);
}

void	ft_error_noc(t_shell *shell, char *str, char *value)
{
	char	*err;

	err = ft_error_line("bash: ", value, str);
	ft_putstr_fd(err, STDERR_FILENO);
	free(err);
	ft_free_shell(shell);
	if (!ft_strcmp(CMD_ERR, str))
		g_status = 127;
	else if (!ft_strcmp(MALL_ERR, str))
		g_status = 2;
	else if (!ft_strcmp(OPEN_ERR, str))
		g_status = 1;
	else if (!ft_strcmp(FILE_NOT_EXE, str))
		g_status = 126;
	else if (!ft_strcmp(NO_FILE, str) || !ft_strcmp(SYNTAX_ERR, str)
		|| !ft_strcmp(NA_FILE, str) || !ft_strcmp(SYNTAX_ERR2, str))
		g_status = 1;
}

void	ft_free_exit(t_shell *shell)
{
	ft_clear_history(shell);
	ft_free_shell(shell);
	if (shell->env)
		ft_free_mat(shell->env);
	free(shell);
	exit(g_status);
}
