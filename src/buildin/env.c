/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <graiolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:49:58 by graiolo           #+#    #+#             */
/*   Updated: 2023/08/19 16:17:36 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_env(t_shell *shell, char **arg)
{
	int	i;

	i = 0;
	if ((arg != NULL && arg[0] != NULL && arg[1] != NULL))
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		g_status = 127;
		return ;
	}
	while (shell->env[i] != NULL)
	{
		if (ft_strchr(shell->env[i], '='))
			ft_printf("%s\n", shell->env[i]);
		i++;
	}
	g_status = 0;
}
