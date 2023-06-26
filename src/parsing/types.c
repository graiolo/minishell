/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:57:54 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/04 18:23:21 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_norm_type_arg(t_token *token)
{
	if (ft_strcmp(token->str, ">") == 0)
		token->type = OUTPUT;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = OAPPEND;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = IAPPEND;
	else if (ft_strcmp(token->str, "<>") == 0)
		token->type = OWRITE;
}

void	ft_type_arg(t_token *token)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (!ft_strcmp(token->str, ">") || !ft_strcmp(token->str, ">>")
		|| !ft_strcmp(token->str, "<") || !ft_strcmp(token->str, "<<")
		|| !ft_strcmp(token->str, "<>"))
		ft_norm_type_arg(token);
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0)
		token->type = COMMA;
	else if (ft_strcmp(token->str, "||") == 0)
		token->type = OR;
	else if (ft_strcmp(token->str, "&&") == 0)
		token->type = AND;
	else if (ft_strcmp(token->str, "(") == 0)
		token->type = OBRACKETS;
	else if (ft_strcmp(token->str, ")") == 0)
		token->type = CBRACKETS;
	else if (ft_is_types(token->prev, "WITOA") == 1)
		token->type = IOFILE;
	else if (token->prev == NULL || token->prev->type >= PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

int	ft_is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

static int	ft_norm_is_types(t_token *token, char *types)
{
	if (ft_strchr(types, 'I') && ft_is_type(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'T') && ft_is_type(token, IAPPEND))
		return (1);
	else if (ft_strchr(types, 'O') && ft_is_type(token, OUTPUT))
		return (1);
	else if (ft_strchr(types, 'A') && ft_is_type(token, OAPPEND))
		return (1);
	else if (ft_strchr(types, 'H') && ft_is_type(token, IOFILE))
		return (1);
	else if (ft_strchr(types, 'W') && ft_is_type(token, OWRITE))
		return (1);
	else if (ft_strchr(types, 'B') && ft_is_type(token, OBRACKETS))
		return (1);
	else if (ft_strchr(types, 'L') && ft_is_type(token, CBRACKETS))
		return (1);
	return (0);
}

int	ft_is_types(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && ft_is_type(token, EMPTY))
		return (1);
	else if (ft_strchr(types, 'D') && ft_is_type(token, CMD))
		return (1);
	else if (ft_strchr(types, 'X') && ft_is_type(token, ARG))
		return (1);
	else if (ft_strchr(types, 'P') && ft_is_type(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && ft_is_type(token, AND))
		return (1);
	else if (ft_strchr(types, 'R') && ft_is_type(token, OR))
		return (1);
	else if (ft_strchr(types, 'C') && ft_is_type(token, COMMA))
		return (1);
	return (ft_norm_is_types(token, types));
}
