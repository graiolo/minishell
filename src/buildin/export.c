/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:24:32 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/13 11:34:27 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static int	ft_count_mat_elem(char **mat)
{
	int	i;

	i = 0;
	while (mat != NULL && mat[i] != NULL)
		i++;
	return (i);
}

static void	ft_norm_export(t_shell *shell, char **new,
	int	*cp_len, int *cp_n_len)
{
	int	len;
	int	n_len;

	len = ft_count_mat_elem(shell->env);
	n_len = ft_count_mat_elem(new);
	n_len += len;
	*cp_len = len;
	*cp_n_len = n_len;
	g_status = 0;
}

static	void	ft_no_args_export(t_shell *shell, int i, int eq, int j)
{
	char	**sort_env;

	sort_env = ft_sort_env(shell->env);
	while (sort_env != NULL && sort_env[i] != NULL)
	{
		j = 0;
		ft_printf("declare -x ");
		while (sort_env[i][j] != 0)
		{
			write(1, &sort_env[i][j], 1);
			if (sort_env[i][j] == '=' && eq == 0)
			{
				write(1, "\"", 1);
				eq++;
			}
			j++;
		}
		if (eq == 1)
			write(1, "\"", 1);
		printf("\n");
		eq = 0;
		i++;
	}
	ft_free_mat(sort_env);
}

void	ft_export(t_shell *shell, char **new)
{
	int	eq;
	int	j;
	int	i;
	int	len;
	int	n_len;

	i = 0;
	eq = 0;
	j = 0;
	ft_norm_export(shell, new, &len, &n_len);
	if (new != NULL && new[1] == NULL)
		ft_no_args_export(shell, eq, i, j);
	else
	{
		while (new[++i] != NULL)
		{
			ft_unset(shell, &new[i - 1]);
			shell->env = ft_realloc(shell->env, sizeof(char *) * (n_len));
			len = ft_count_mat_elem(shell->env);
			shell->env[len] = ft_strdup(new[i]);
		}
		shell->env[++len] = NULL;
	}
}
