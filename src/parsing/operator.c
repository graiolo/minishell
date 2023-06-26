/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:25:19 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/17 00:26:22 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_operator(t_shell *shell, t_token *token)
{
	t_token	*prev;

	prev = token;
	if (token != NULL && ft_is_types(token, "PERC"))
		ft_error_noc(shell, SYNTAX_ERR2, token->str);
	while (token != NULL)
	{
		if (ft_is_types(token, "PERC") == 1 && token->next != NULL
			&& ft_is_types(token->next, "PERC") == 1)
			return (ft_error_noc(shell, SYNTAX_ERR2, token->next->str));
		prev = token;
		token = token->next;
	}
	if (prev != NULL)
		if (ft_is_types(prev, "PERC"))
			ft_get_token(shell, readline("> "));
}
