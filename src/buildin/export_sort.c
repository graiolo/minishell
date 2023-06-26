/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:34:43 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/13 11:34:51 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static void	ft_norm_sort_env(int *cp_i, int *cp_j, char **new)
{
	char	*temp;
	int		i;
	int		j;

	i = *cp_i;
	j = *cp_j;
	if (new[j + 1] != NULL && strcmp(new[j], new[j + 1]) > 0)
	{
		temp = ft_strdup(new[j]);
		free(new[j]);
		new[j] = new[j + 1];
		new[j + 1] = temp;
		i = 0;
		j = -1;
	}
	*cp_i = i;
	*cp_j = j;
}

char	**ft_sort_env(char **env)
{
	int		i;
	int		j;
	int		rows;
	char	**new;

	i = 0;
	j = 0;
	while (env != NULL && env[i] != NULL)
		i++;
	rows = i;
	new = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (new != NULL && env[++i] != NULL)
		new[i] = ft_strdup(env[i]);
	i = 0;
	while (i < rows)
	{
		while (j < rows)
		{
			ft_norm_sort_env(&i, &j, new);
			j++;
		}
		i++;
	}
	return (new);
}
