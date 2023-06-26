/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:45:43 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/24 15:34:50 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	*ft_get_path_help(char **split, char *cmd, int i, char *tmp)
{
	if (split[i][ft_strlen(split[i]) - 1] != '/')
	{
		tmp = ft_strjoin(split[i], "/");
		tmp = ft_free_join(tmp, cmd, 1);
	}
	else
		tmp = ft_strjoin(split[i], cmd);
	return (tmp);
}

char	*ft_get_path_cmd(t_shell *shell, char *cmd)
{
	char	**split;
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strchr(cmd, '/') != NULL
		|| !ft_getenv(shell, "PATH"))
		return (ft_strdup(cmd));
	split = ft_split(ft_getenv(shell, "PATH"), ':');
	while (split != NULL && split[i])
	{
		tmp = ft_get_path_help(split, cmd, i, tmp);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			ft_free_mat(split);
			return (tmp);
		}
		i++;
		free(tmp);
	}
	ft_free_mat(split);
	return (ft_strdup(cmd));
}

int	ft_cmd_sep(t_cmd *cmd, t_token *tok)
{
	if (tok->type == PIPE)
	{
		if (tok->next && tok->next->type == PIPE
			&& tok->prev && tok->prev->type == PIPE)
			cmd->pipe = 3;
		if (tok->next && tok->next->type == PIPE
			&& (!tok->prev || tok->prev->type != PIPE))
			cmd->pipe = 1;
		if (tok->prev && tok->prev->type == PIPE && (!tok->next
				|| tok->next->type != PIPE))
			cmd->pipe = 2;
		return (PIPE);
	}
	if (tok->type == OR)
		return (OR);
	if (tok->type == COMMA)
		return (COMMA);
	if (tok->type == AND)
		return (AND);
	return (0);
}

char	**ft_cmdmat(t_shell *shell, t_token *n_tok, char *cmd)
{
	char	**args;
	int		i;
	t_token	*ptr;

	if (!n_tok)
		return (NULL);
	ptr = n_tok;
	i = ft_tok_tobreak(n_tok, "next");
	args = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!args)
		return (NULL);
	if (ft_is_builtin(cmd) == 1)
		args[0] = ft_strdup(cmd);
	else
		args[0] = ft_get_path_cmd(shell, cmd);
	ptr = n_tok->next;
	i = 1;
	while (ptr && ptr->type == ARG)
	{
		args[i++] = ft_strdup(ptr->str);
		ptr = ptr->next;
	}
	return (args);
}

void	ft_free_cmd(t_cmd	**head)
{
	t_cmd	*node;

	if (head != NULL && *head != NULL)
	{
		while (*head != NULL)
		{
			node = *head;
			*head = (*head)->next;
			ft_free_mat(node->tab);
			free(node);
		}
	}
}
