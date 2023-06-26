/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:57:00 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/17 02:16:58 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

t_cmd	*ft_add_cmd_help(t_shell *shell, char **tab, int i)
{
	t_cmd	*new;
	int		j;

	j = 0;
	new = NULL;
	new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (new == NULL)
		ft_error(shell, MALL_ERR, 0, NULL);
	ft_init_cmd(new);
	if (tab != NULL)
	{
		new->tab = (char **)ft_calloc(i + 1, sizeof(char *));
		if (new->tab == NULL)
			ft_error(shell, MALL_ERR, 0, NULL);
		while (j < i)
		{
			new->tab[j] = ft_strdup(tab[j]);
			if (new->tab[j] == NULL)
				ft_error(shell, MALL_ERR, 0, NULL);
			j++;
		}
	}
	return (new);
}

t_cmd	*ft_add_cmd_back(t_shell *shell, t_cmd **head, char **tab, t_token *tok)
{
	t_cmd	*new;
	t_cmd	*tmp;
	int		i;

	i = 0;
	new = NULL;
	tmp = NULL;
	while (tab && tab[i] != NULL)
		i++;
	new = ft_add_cmd_help(shell, tab, i);
	if (tok)
		new = ft_redir_in(tok, new);
	new->next = NULL;
	tmp = *head;
	if (*head == NULL)
	{
		new->prev = NULL;
		*head = new;
		return (new);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (new);
}

void	ft_read_tok(t_shell *shell)
{
	t_token	*tok;
	int		redir;

	tok = shell->token;
	if (tok == NULL)
		return ;
	if (ft_is_types(tok, "PERCL") == 1)
		return (ft_error_noc(shell, SYNTAX_ERR, NULL));
	while (tok != NULL)
	{
		redir = ft_check_redir(tok);
		if (redir == -1)
			return (ft_error_noc(shell, NA_FILE, NULL));
		if (redir == -2)
			return (ft_error_noc(shell, NULL, NULL));
		tok = ft_read_cmd(shell, tok);
		if (tok != NULL)
			tok = tok->next;
		else
			break ;
	}
	if (shell->cmd != NULL)
		ft_exec (shell, shell->cmd);
}
