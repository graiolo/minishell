/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:09:41 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/16 17:31:05 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

int	ft_brackets(char *str, int len)
{
	int	i;
	int	n_brac;

	i = 0;
	n_brac = 0;
	while (i < len)
	{
		if (ft_quotes(str, i) != 2)
		{
			if (str[i] == '(')
				n_brac++;
			if (str[i] == ')')
				n_brac--;
			if (n_brac < 0)
				n_brac = INT_MIN;
		}
		i++;
	}
	return (n_brac);
}
