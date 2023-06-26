/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:27:58 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/23 11:55:48 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

t_cmd	*ft_and(t_shell *shell, t_cmd *ptr, char **env)
{
	if (ptr->sep == AND)
	{
		ft_simple_cmd(shell, ptr, env);
		if (g_status != 0)
		{
			if (ptr->next->type == OBRACKETS)
			{
				while (ptr && ptr->type != CBRACKETS)
					ptr = ptr->next;
				return (ptr);
			}
			else
			{
				while ((ptr && (ptr->sep == PIPE || ptr->sep == AND)
						&& ptr->type != CBRACKETS && ptr->next))
					ptr = ptr->next;
				return (ptr);
			}
		}
		else
			return (ptr);
	}
	return (ptr);
}

t_cmd	*ft_comma(t_shell *shell, t_cmd *ptr, char **env)
{
	while (ptr->sep == COMMA && ptr->next)
	{
		ft_simple_cmd(shell, ptr, env);
		ptr = ptr->next;
	}
	return (ptr);
}

t_cmd	*ft_or(t_shell *shell, t_cmd *ptr, char **env)
{
	ft_simple_cmd(shell, ptr, env);
	if (g_status == 0)
	{
		if (ptr->next && ptr->next->type == OBRACKETS)
		{
			ptr = ptr->next;
			while (ptr && ptr->type != CBRACKETS && ptr->next)
				ptr = ptr->next;
		}
		while (ptr && ((ptr->sep == PIPE || ptr->sep == OR)
				|| (ptr->type != CBRACKETS && ptr->next)))
			ptr = ptr->next;
		if (ptr->next && ptr->type == CBRACKETS && ptr->sep != AND)
			ptr = ptr->next;
		return (ptr);
	}
	else
		return (ptr);
}
