/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:16:22 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/03 20:47:50 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

int	ft_sub_str(char *str, char *sub)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == sub[0])
		{
			j = 0;
			while (sub[j] != '\0' && str[i + j] == sub[j])
				j++;
			if (sub[j] == '\0')
				return (0);
			if (str[i + j] == '\0')
				return (1);
		}
	}
	return (1);
}

int	ft_right_compare(char *files, char *card)
{
	int	i;

	i = 0;
	while (files[i] != 0 && card[i] != 0 && files[i] == card[i])
		i++;
	if (card[i] == 0)
		return (0);
	return (1);
}

int	ft_left_compare(char *files, char *card)
{
	int	c_len;
	int	f_len;

	c_len = ft_strlen(card);
	f_len = ft_strlen(files);
	if (c_len > f_len)
		return (1);
	while (c_len != -1)
		if (files[f_len--] != card[c_len--])
			return (1);
	return (0);
}
