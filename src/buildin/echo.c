/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:04:36 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/03 20:44:01 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_echo(t_shell *shell, char **str)
{
	int	i;
	int	flag;

	(void)shell;
	i = 1;
	flag = false;
	if (str != NULL && str[0] != NULL && str[1] != NULL)
	{
		if (ft_strcmp(str[1], "-n") == 0)
		{
			flag = TRUE;
			i = 2;
		}
	}
	while (str != NULL && str[i] != NULL)
	{
		ft_printf("%s", str[i++]);
		if (str[i] != NULL)
			ft_printf(" ");
	}
	if (flag == false)
		ft_printf("\n");
	g_status = 0;
}
