/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:10:16 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/13 11:16:32 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	*ft_add_back(t_token **head, char *line)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *head;
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->str = ft_strdup(line);
	if (*head == NULL)
	{
		new->prev = NULL;
		ft_type_arg(new);
		*head = new;
		return (new);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	ft_type_arg(new);
	return (new);
}

void	ft_free_list(t_token **head)
{
	while (head != NULL && *head != NULL)
		ft_remove_head(head);
	free(*head);
	*head = NULL;
}

void	ft_remove_head(t_token **head)
{
	t_token	*node;
	t_token	*token;

	token = *head;
	if (token != NULL)
	{
		free(token->str);
		node = token;
		token = token->next;
		free(node);
		if (token != NULL)
			token->prev = NULL;
	}
	*head = token;
}

void	ft_remove_node(t_token **head, t_token *node)
{
	t_token	*tmp;

	tmp = *head;
	if (tmp == node)
	{
		*head = tmp->next;
		if (tmp->next != NULL)
			tmp->next->prev = NULL;
		free(tmp->str);
		free(tmp);
		return ;
	}
	while (tmp != NULL && tmp != node)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	free(tmp->str);
	free(tmp);
}

t_token	*ft_new_node(char *str, int typo)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->str = ft_strdup(str);
	new->type = typo;
	return (new);
}
