/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:45:05 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 15:43:11 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static char	*ft_get_session(t_shell *shell)
{
	char	line[1024];
	int		i;
	int		start;

	i = 0;
	line[0] = 0;
	if (ft_getenv(shell, "SESSION_MANAGER") != NULL)
		ft_strcpy(line, ft_getenv(shell, "SESSION_MANAGER"));
	while (line[i] != 0 && line[i] != '/')
		i++;
	if (i != 0)
		start = ++i;
	else
		start = i;
	i = -1;
	if (ft_getenv(shell, "SESSION_MANAGER") == NULL)
		ft_strcpy(line, ft_getenv(shell, "NAME"));
	while (++i != 1024 && line[start + i] != 0 && line[start + i] != '.')
		line[i] = line[start + i];
	line[i] = 0;
	return (ft_strdup(line));
}

static char	*ft_norm_return(char *line, char *pwd)
{
	line = ft_free_join(line, pwd, 1);
	return (ft_free_join(line, "$ ", 1));
}

char	*ft_read_line(int argc, char **argv, t_shell *shell)
{
	size_t	len;
	int		i;
	char	*line;
	char	pwd[1024];

	i = -1;
	(void)argc;
	(void)argv;
	line = ft_strjoin(ft_getenv(shell, "USER"), "@");
	line = ft_free_join(line, ft_get_session(shell), 3);
	line = ft_free_join(line, ":", 1);
	getcwd(pwd, 1024);
	len = ft_strlen(ft_getenv(shell, "HOME"));
	if (ft_strncmp(pwd, ft_getenv(shell, "HOME"), len) != 0)
		return (ft_norm_return(line, pwd));
	pwd[0] = '~';
	while (len != 0 && pwd[++i + len] != 0)
		pwd[i + 1] = pwd[i + len];
	pwd[i + 1] = 0;
	return (ft_norm_return(line, pwd));
}
