/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:07:30 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/16 14:09:59 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_read(t_shell *shell, char **new)
{
	char	*pew;

	(void)shell;
	(void)new;
	pew = readline(NULL);
	if (ft_strlen(pew) == 0)
		printf("\n");
	g_status = 0;
}
