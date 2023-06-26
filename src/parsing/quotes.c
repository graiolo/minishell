/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:18:11 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 17:17:41 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static int	ft_norm_quotes(char *str, int len, int i, int open)
{
	(void)len;
	if (i > 0 && str[i - 1] == '\\' && open != 1)
	{
		if (open == 0 && i > 1 && str[i - 2] == '\\')
		{
			if (str[i] == '\'')
				open = 1;
			if (str[i] == '\"')
				open = 2;
		}
		else if (open == 2 && str[i] == '\"'
			&& i > 1 && str[i - 2] == '\\')
			open = 0;
	}
	return (open);
}

int	ft_quotes(char *str, int len)
{
	int	open;
	int	i;

	open = 0;
	i = 0;
	while (i < len)
	{
		if (i > 0 && str[i - 1] == '\\' && open != 1)
			open = ft_norm_quotes(str, len, i, open);
		else if (str[i] == '\'' && open == 0)
			open = 1;
		else if (str[i] == '\"' && open == 0)
			open = 2;
		else if (str[i] == '\'' && open == 1)
			open = 0;
		else if (str[i] == '\"' && open == 2)
			open = 0;
		i++;
	}
	return (open);
}

static void	ft_norm_line_space(char *str, char *line, int *cp_i, int *cp_j)
{
	int	i;
	int	j;

	i = *cp_i;
	j = *cp_j;
	line[j++] = ' ';
	line[j++] = str[i++];
	if (str[i] != 0 && str[i] == '>' && line[j - 1] == '<')
		line[j++] = str[i++];
	else if (str[i] != 0 && ft_is_sep(str, i) == 1 && line[j - 1] == str[i])
		if (!(str[i] == ')' || str[i] == '('))
			line[j++] = str[i++];
	line[j++] = ' ';
	*cp_i = i;
	*cp_j = j;
}

char	*ft_line_space(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = (char *)ft_calloc(strlen(str) + 1024, 1);
	while (line != NULL && str[i] != 0)
	{
		if ((str[i] == '$' && ft_quotes(str, i) != 1 && i
				&& str[i - 1] != '\\') || (str[i] == '$' && i == 0))
			line[j++] = ((char)-str[i++]);
		else if (str[i] == '*' && ft_quotes(str, i) == 0)
			line[j++] = ((char)-str[i++]);
		else if (str[i] == '~' && ft_quotes(str, i) == 0)
			line[j++] = ((char)-str[i++]);
		else if (ft_is_sep(str, i) == 1)
			ft_norm_line_space(str, line, &i, &j);
		else
			line[j++] = str[i++];
	}
	return (line);
}
