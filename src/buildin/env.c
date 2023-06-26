/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:49:58 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/03 20:43:59 by graiolo          ###   ########.fr       */
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
		ft_printf("%s\n", shell->env[i++]);
	g_status = 0;
}
