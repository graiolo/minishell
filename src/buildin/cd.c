/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:21:07 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 17:35:52 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static void	ft_norm_too_args(char *error)
{
	free(error);
	write(STDERR_FILENO, "minishell: cd: Too many arguments\n", 35);
	g_status = 1;
}

static void	ft_norm_folder_not_found(char *error)
{
	perror(error);
	free(error);
	g_status = 1;
}

void	ft_cd(t_shell *shell, char **path)
{
	char	*error;

	if (path != NULL && path[0] != NULL && path[1] == NULL)
	{
		if (ft_getenv(shell, "HOME") == NULL)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
			g_status = 1;
			return ;
		}
		chdir(ft_getenv(shell, "HOME"));
	}
	else if (path != NULL && path[0] != NULL && path[1] != NULL)
	{
		error = ft_strjoin("minishell: cd: ", path[1]);
		if (path[2] != NULL)
			return (ft_norm_too_args(error));
		else if (chdir(path[1]) == -1)
			return (ft_norm_folder_not_found(error));
		free(error);
	}
	g_status = 0;
}
