/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:39:33 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/14 20:19:59 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

typedef struct s_bra
{
	int	obra;
	int	cbra;
}	t_bra;

static t_token	*ft_norm_second(int i, t_bra bra, t_cmd *tmp, t_token *tok)
{
	if (i > 0)
		tok = ft_next_sep(tok);
	if (tok != NULL && tmp != NULL)
	{
		tmp->sep = ft_cmd_sep(tmp, tok);
		if (bra.obra > 0)
			tmp->type = OBRACKETS;
		if (bra.cbra > 0)
			tmp->type = CBRACKETS;
	}
	return (tok);
}

t_token	*ft_norm_fist(t_shell *shell, t_token *tok, char ***args)
{
	if (tok->type == CMD || tok->type == IAPPEND)
	{
		if (tok->type == IAPPEND)
			*args = ft_here_cmd(tok);
		else
			*args = ft_cmdmat(shell, tok, tok->str);
		while (tok && (tok->type == CMD || tok->type == ARG))
			tok = tok->next;
	}
	return (tok);
}

t_cmd	*ft_read_cmd_help(t_shell *shell, t_token *tok, char **args, int i)
{
	t_cmd	*tmp;

	if (i > 0)
		tmp = ft_add_cmd_back(shell, &shell->cmd, args, tok);
	else
		tmp = ft_add_cmd_back(shell, &shell->cmd, args, NULL);
	return (tmp);
}

t_token	*ft_read_cmd(t_shell *shell, t_token *tok)
{
	char	**args;
	t_cmd	*tmp;
	int		i;
	t_bra	bra;

	bra.obra = 0;
	bra.cbra = 0;
	args = NULL;
	i = ft_check_redir(tok);
	if (tok->type == OBRACKETS)
	{
		bra.obra++;
		tok = tok->next;
	}
	tok = ft_norm_fist(shell, tok, &args);
	if (tok && tok->type == CBRACKETS)
	{
		bra.cbra++;
		tok = tok->next;
	}
	tmp = ft_read_cmd_help (shell, tok, args, i);
	tok = ft_norm_second(i, bra, tmp, tok);
	ft_free_mat(args);
	return (tok);
}
