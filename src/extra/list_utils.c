/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <graiolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:16:18 by graiolo           #+#    #+#             */
/*   Updated: 2023/08/22 17:18:29 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_join_list(t_token **cmd, t_token **red, t_token **new)
{
	t_token	*tmp;
	t_token	*tmp3;

	tmp = *cmd;
	tmp3 = *new;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp != NULL)
		tmp->next = *red;
	if (tmp == NULL && *red != NULL)
		*new = *red;
	else if (tmp3 == NULL )
		*new = *cmd;
	else
	{
		while (tmp3 != NULL && tmp3->next != NULL)
			tmp3 = tmp3->next;
		tmp3->next = *cmd;
	}
	*cmd = NULL;
	*red = NULL;
}

void	ft_update_prev(t_token *token)
{
	t_token	*prev;

	prev = NULL;
	while (token != NULL)
	{
		token->prev = prev;
		prev = token;
		token = token->next;
	}
}

void	ft_printf_list(t_token *token)
{
	printf("input: ");
	while (token != NULL)
	{
		printf("%s(%d) ", token->str, token->type);
		token = token->next;
	}
	printf("\n");
}
