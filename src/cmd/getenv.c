/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:24:57 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/23 12:18:42 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	*ft_getenv(t_shell *shell, const char *var)
{
	int	i;

	i = 0;
	if (var == NULL)
		return (NULL);
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var) - 1) == 0
			&& shell->env[i][ft_strlen(var)] != 0
			&& shell->env[i][ft_strlen(var)] == '=')
			return (&shell->env[i][ft_strlen(var) + 1]);
		i++;
	}
	return (NULL);
}
