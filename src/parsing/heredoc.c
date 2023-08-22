/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <graiolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:55:30 by graiolo           #+#    #+#             */
/*   Updated: 2023/08/22 19:58:10 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_heredoc(t_shell *shell)
{
	t_token	*local;
	t_token	*new;

	if (shell->token)
	{
		if (shell->token->type == IAPPEND && shell->token->next
			&& shell->token->next->type == IOFILE)
		{
			local = shell->token->next;
			if (local->next)
			{
				new = ft_new_node(";", COMMA);
				new->next = local->next;
				local->next = new;
			}
		}
	}
}
