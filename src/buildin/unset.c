/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:52:11 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/03 20:44:18 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

typedef struct s_arry
{
	int		i;
	int		j;
	int		k;
}	t_array;

static int	ft_envcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 != '=' && *s2 != '=' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 && !*s2 && *s1 == '=')
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	ft_init_arr(t_array *arr)
{
	arr->i = 0;
	arr->j = 0;
	arr->k = 0;
}

void	ft_unset(t_shell *shell, char **del)
{
	char	**new;
	t_array	arr;

	ft_init_arr(&arr);
	if (!(del != NULL && del[0] != NULL && del[1] != NULL))
		return (g_status = 0, ft_putstr_fd("unset: not enough arguments\n", 2));
	new = malloc(malloc_usable_size(shell->env));
	while (shell->env != NULL && shell->env[arr.i] != NULL)
	{
		while (del[arr.j] != NULL)
		{
			if (ft_envcmp(shell->env[arr.i], del[arr.j]) != 0)
				arr.j++;
			else
				break ;
		}
		if (del[arr.j] == NULL)
			new[arr.k++] = ft_strdup(shell->env[arr.i]);
		arr.j = 1;
		++arr.i;
	}
	new[arr.k] = NULL;
	ft_free_mat(shell->env);
	shell->env = new;
	g_status = 0;
}
