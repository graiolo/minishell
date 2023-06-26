/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:23:54 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/04 18:39:10 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_exit(t_shell *shell, char **status)
{
	rl_clear_history();
	ft_printf("exit");
	if (status != NULL && status[0] != NULL && status[1] != NULL)
		g_status = ft_atoi(status[1]) % 256;
	else
		g_status = 0;
	ft_free_exit(shell);
}
