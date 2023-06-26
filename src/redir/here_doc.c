/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:58:23 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/16 16:12:59 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	**ft_here_cmd(t_token *tok)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	if (args == NULL)
		return (NULL);
	args[0] = ft_strdup(tok->str);
	if (tok->next != NULL)
		args[1] = ft_strdup(tok->next->str);
	else
		args[1] = NULL;
	args[2] = NULL;
	return (args);
}

void	ft_here_doc(t_shell *shell, t_cmd *cmd)
{
	int		fd;
	char	*line;

	if (cmd->tab[1] == NULL)
		return (ft_error_noc(NULL, NA_FILE, NULL));
	if (cmd->red_out != 1)
		fd = dup(cmd->red_out);
	else
		fd = open(".here_docxxx", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error_noc(shell, NO_FILE, NULL);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, cmd->tab[1]) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	cmd->red_out = dup(fd);
	unlink(".here_docxxx");
	close(fd);
}
