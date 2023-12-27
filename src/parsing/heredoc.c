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

	local = shell->token;
	while (local)
	{
		if (local->type == IAPPEND)
		{
			while (local->next && ft_is_types(local->next, "WITOAH") == 1)
				local = local->next;
			if (local->next && ft_is_types(local->next, "PERC") != 1)
			{
				new = ft_new_node("|", PIPE);
				new->next = local->next;
				local->next = new;
			}
		}
		local = local->next;
	}
}
