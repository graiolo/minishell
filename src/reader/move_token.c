/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:41:44 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/03 20:48:26 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

t_token	*ft_prev_sep(t_token *tok)
{
	while (tok != NULL && tok->type != PIPE && tok->type != COMMA
		&& tok->type != AND && tok->type != OR)
		tok = tok->prev;
	return (tok);
}

t_token	*ft_next_sep(t_token *tok)
{
	while (tok != NULL && tok->type != PIPE && tok->type != COMMA
		&& tok->type != AND && tok->type != OR)
		tok = tok->next;
	return (tok);
}

int	ft_tok_tobreak(t_token *tok, char *direction)
{
	int	i;

	i = 0;
	if (ft_strcmp("next", direction) == 0)
	{
		while (tok != NULL && tok->type != PIPE && tok->type != COMMA
			&& tok->type != AND && tok->type != OR)
		{
			tok = tok->next;
			i++;
		}
	}
	else
	{
		while (tok != NULL && tok->type != PIPE && tok->type != COMMA
			&& tok->type != AND && tok->type != OR)
		{
			tok = tok->prev;
			i++;
		}
	}
	return (i);
}
