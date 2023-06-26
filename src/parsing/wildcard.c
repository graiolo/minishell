/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:16:49 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/23 11:52:02 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

/*
	while (new != NULL && new[i] != NULL)
		ft_add_back(&token_list, new[i++]);
	if (token_list == NULL)
	{
		free((*token)->str);
		(*token)->str = ft_strdup("");
		ft_free_mat(new);
		return ;
	}
	*token = token_list;
*/

static void	ft_clean_wildcard(char **old, t_shell *shell)
{
	char	*str;
	char	*new;
	int		i;
	int		j;

	str = old[0];
	new = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (new == NULL)
		ft_error(shell, MALL_ERR, 0, NULL);
	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		if (str[i] == - '*' && j != 0 && new[j - 1] == - '*')
			;
		else
			new[j++] = str[i];
		i++;
	}
	free(str);
	*old = new;
}

static void	ft_norm_wildcard_free(char	**new, t_token *token_rmv)
{
	ft_free_mat(new);
	free(token_rmv->str);
	free(token_rmv);
}

static void	ft_norm_wildcard(t_list_token *t, t_shell *shell)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_card(shell, t->tmp->str);
	if (new != NULL && new[i] == NULL)
		new[i] = ft_strdup(t->tmp->str);
	while (new != NULL && new[i] != NULL)
		ft_add_back(&(t->token_list), new[i++]);
	*(t->token) = t->token_list;
	if (t->tmp != NULL && t->tmp->prev != NULL)
		t->tmp->prev->next = t->token_list;
	else
		t->token_list->prev = t->tmp->prev;
	while (t->token_list->next != NULL)
		t->token_list = t->token_list->next;
	t->token_list->next = t->tmp->next;
	if (t->tmp->next != NULL)
		t->tmp->next->prev = t->token_list;
	ft_norm_wildcard_free(new, t->token_rmv);
}

static void	ft_file_not_found(t_shell *shell, t_token **token, char *old)
{
	t_token	*tmp;

	tmp = shell->token;
	while (tmp != NULL && tmp != *token)
		tmp = tmp->next;
	if (tmp == NULL)
		return (free(old));
	if (ft_strchr(tmp->str, - '*') != NULL)
	{
		free(tmp->str);
		tmp->str = old;
	}
	else
		free(old);
}

void	ft_wildcard(t_shell *shell, t_token **token)
{
	t_list_token	list;
	int				i;
	char			*old;

	i = 0;
	old = NULL;
	list.tmp = shell->token;
	list.token_rmv = *token;
	list.token_list = NULL;
	while (list.tmp != NULL && list.tmp != *token)
		list.tmp = list.tmp->next;
	if (list.tmp == NULL || list.tmp->str == NULL)
		return ;
	if (ft_strchr(list.tmp->str, - '*'))
		old = ft_strdup(list.tmp->str);
	if (ft_strchr(list.tmp->str, - '*'))
		ft_clean_wildcard(&list.tmp->str, shell);
	while (list.tmp->str[i] != - '*' && list.tmp->str[i] != '\0')
		i++;
	list.token = token;
	if (list.tmp->str[i] == - '*')
		ft_norm_wildcard(&list, shell);
	ft_file_not_found(shell, token, old);
}
