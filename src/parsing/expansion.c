/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 21:49:16 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 20:35:31 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static char	*ft_is_tilde(char *str)
{
	char	*home;

	home = NULL;
	if (str == NULL)
		return (str);
	if (str[0] != 0 && str[0] == - '~')
	{
		if (ft_strlen(str) == 1 || (str[1] != 0 && str[1] == '/'))
		{
			home = ft_strjoin(getenv("HOME"), &str[1]);
			free(str);
			return (home);
		}
	}
	return (str);
}

void	*ft_expand(t_shell *shell, char *str)
{
	char	*env;
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	env = NULL;
	str = ft_is_tilde(str);
	while (str != NULL && str[i] != 0)
	{
		while (str[i] != 0 && str[i] != - '$')
		{
			new = ft_realloc_str(new, ft_strlen(new) + 1);
			new[ft_strlen(new)] = str[i];
			i++;
		}
		if (str[i] == 0)
			break ;
		i++;
		env = ft_get_env_varible(shell, str, &i);
		if (env != NULL)
			new = ft_free_join(new, env, 1);
	}
	free(str);
	return (new);
}

char	*ft_get_env_varible(t_shell *shell, char *str, int *len)
{
	char	*name;
	char	*env;
	int		j;
	int		i;

	j = 0;
	i = *len;
	name = NULL;
	name = ft_calloc(1, 1);
	while (str[i] != 0 && !ft_strchr("<\\>\'.|$\"; *&", str[i])
		&& str[i] != - '$' && str[i] != - '*')
	{
		name = ft_realloc_str(name, ft_strlen(name) + 2);
		name[j++] = str[i++];
		if (name[j - 1] == '?')
			break ;
	}
	*len = i;
	if (name[0] == '?' && ft_strlen(name) == 1)
		return (free(name), ft_itoa_no_malloc(g_status));
	env = ft_getenv(shell, (const char *)name);
	if ((env == NULL && name[0] == 0 && ft_quotes(str, i) != 0)
		|| ((ft_strcmp(str, "-$") && ft_strlen(str) == 1)))
		return (free(name), "$");
	return (free(name), env);
}
