/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:20:39 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/16 18:46:22 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	**ft_get_env(char **env)
{
	char	**my_env;
	int		i;

	i = 0;
	while (env != NULL && env[i])
		i++;
	my_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

int	ft_check_redir(t_token *tok)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (tok != NULL && tok->type != PIPE && tok->type != COMMA
		&& tok->type != AND && tok->type != OR)
	{
		if (tok->type == INPUT || tok->type == OUTPUT
			|| tok->type == IAPPEND || tok->type == OAPPEND)
		{
			if (ft_is_types(tok, "ITOAHW") == 1 && tok->next == NULL)
				return (-1);
			if (tok->type == INPUT && (tok->next->str == NULL
					|| open(tok->next->str, O_RDONLY) == -1))
				return (ft_error_noc(NULL, NO_FILE, tok->next->str), -2);
			check++;
		}
		i++;
		tok = tok->next;
	}
	if (check > 0)
		return (check);
	else
		return (FALSE);
}

t_cmd	*ft_redir_in(t_token *tok, t_cmd *cmd)
{
	int	tmp_in;
	int	tmp_out;

	tmp_in = 0;
	tmp_out = 1;
	while (tok != NULL && tok->type != PIPE && tok->type != COMMA
		&& tok->type != AND && tok->type != OR)
	{
		if (tok->type == INPUT && tok->next != NULL)
			tmp_in = open(tok->next->str, O_RDONLY);
		if (tok->type == OUTPUT && tok->next != NULL)
			tmp_out = open(tok->next->str, 01 | 0100 | 01000, 0644);
		if (tok->type == OAPPEND && tok->next != NULL)
			tmp_out = open(tok->next->str, 01 | 0100 | 02000, 0644);
		if (cmd != NULL)
		{
			cmd->red_in = tmp_in;
			cmd->red_out = tmp_out;
		}
		tok = tok->next;
	}
	return (cmd);
}

void	ft_dup_redir(t_cmd *cmd)
{
	if (cmd && cmd->tab && strncmp(cmd->tab[0], "cd", 3))
	{
		if (cmd->red_out != 1)
			dup2(cmd->red_out, STDOUT_FILENO);
		if (cmd->red_in != 0)
			dup2(cmd->red_in, STDIN_FILENO);
	}
}

void	ft_close_redir(t_cmd *cmd)
{
	if (cmd && cmd->tab && ft_strncmp(cmd->tab[0], "cd", 3))
	{
		if (cmd->red_out != 1)
		{
			close(cmd->red_out);
			dup2(1, STDOUT_FILENO);
		}
		if (cmd->red_in != 0)
		{
			close(cmd->red_in);
			dup2(0, STDIN_FILENO);
		}
	}
}
