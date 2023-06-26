/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:10:49 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/23 11:12:00 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//◦ ctrl-C displays a new prompt on a new line.
//  CTRL+C (o SIGINT)   ||      exit status 130

//◦ ctrl-D exits the shell.
//  EOF					||		exit status 0

//◦ ctrl-\ does nothing.
//	CTRL+\ (o SIGQUIT)	||		exit status prev.

#include "./../../include/minishell.h"

void	ft_sig_init(int sign)
{
	(void)sign;
	g_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sig_term(t_shell *shell)
{
	ft_clear_history(shell);
	write(STDOUT_FILENO, "exit\n", 5);
	ft_free_exit(shell);
}
