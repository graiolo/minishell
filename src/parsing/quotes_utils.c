/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:14:29 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/03 20:48:01 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

int	ft_slash(char *str, int len)
{
	int	slash;
	int	i;

	slash = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\\')
			slash++;
		else
			slash = 0;
		i++;
	}
	if (slash % 2 == 0)
		return (0);
	else
		return (1);
}

int	ft_is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;&()", line[i]))
		return (0);
	else if (ft_strchr("<>|;&()", line[i]) && ft_quotes(line, i) == 0)
		return (1);
	return (0);
}

static void	ft_norm_correct_form(char *line, char *new, int *cp_i, int *cp_j)
{
	int	j;
	int	i;

	j = *cp_j;
	i = *cp_i;
	if (ft_isspace(line[i]) == 0 || ft_quotes(line, i) != 0)
		new[j++] = line[i];
	else if (ft_isspace(line[i]) != 0 && i && ft_isspace(line[i - 1]) == 0)
		new[j++] = line[i];
	i++;
	*cp_i = i;
	*cp_j = j;
}

char	*ft_correct_form(char *line)
{
	char	*new;
	int		count;
	int		i;
	int		j;

	i = 0;
	count = ft_strlen(line);
	line = ft_strtrim(line, " ,\n,\r");
	while (line[i] != 0)
	{
		if (i && ft_isspace(line[i - 1]) != 0
			&& ft_isspace(line[i]) != 0 && ft_quotes(line, i) == 0)
			count--;
		i++;
	}
	i = 0;
	j = 0;
	new = ft_calloc(count + 1, 1);
	if (new == NULL)
		return (free(line), NULL);
	while (line[i] != 0)
		ft_norm_correct_form(line, new, &i, &j);
	free(line);
	return (new);
}
