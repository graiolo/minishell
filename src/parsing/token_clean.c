/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:56:22 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/23 11:18:23 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

void	ft_clean_null_cmd(t_token *token)
{
	while(token)
	{
		if(ft_is_types(token, "PERC"))
		{
			token = token->next;
			if (ft_is_type(token, EMPTY))
			{
				token->str = strdup("''");
				token->type = 1;
			}
		}
		if (token)
			token = token->next;
	}
}

void	ft_clean_type(t_shell *shell, t_token *token)
{
	while (token != NULL)
	{
		if (token->type == CMD || token->type == ARG || token->type == IOFILE)
			token->str = ft_expand(shell, token->str);
		if (token->type == ARG)
			ft_wildcard(shell, &token);
		if (token->type == CMD)
			ft_clean_cmd(shell, &token->str);
		else if (token->type == ARG)
			ft_clean_arg(shell, &token->str);
		else if (token->type == IOFILE)
			ft_clean_arg(shell, &token->str);
		if (token->str == NULL || token->str[0] == 0)
			token->type = EMPTY;
		token = token->next;
	}
}

static void	ft_norm_clean_arg(char *arg, char *new, int *cp_i, int *cp_j)
{
	int	i;
	int	j;

	i = *cp_i;
	j = *cp_j;
	if ((!ft_strcmp(arg, "\\\'") || !ft_strcmp(arg, "\\\"")) && j == 0)
		;
	else if (!ft_strcmp(arg, "\\\'") || !ft_strcmp(arg, "\\\""))
		new[i++] = arg[j];
	else if ((arg[j] == '\'' && ft_quotes(arg, j) != 2)
		|| (arg[j] == '\"' && ft_quotes(arg, j) != 1))
		;
	else if (!(arg[j] == '\'' && arg[j] == '\"'))
		new[i++] = arg[j];
	else if (!(arg[j] == '\\' && arg[j + 1]
			&& ft_strchr("<\\>\'|$\";&()", arg[j + 1])))
		new[i++] = arg[j];
	else if (arg [j + 1] && (((arg [j + 1] == '\'')
				&& ft_quotes(arg, j) == 2)
			|| ((arg [j + 1] == '\"') && ft_quotes(arg, j) == 1)))
		new[i++] = arg[j];
	j++;
	*cp_i = i;
	*cp_j = j;
}

void	ft_clean_arg(t_shell *shell, char **str)
{
	char	*new;
	char	*arg;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arg = *str;
	if (arg == NULL)
		return ;
	len = ft_strlen(arg);
	new = ft_calloc(1, len + 1);
	if (new == NULL)
		ft_error(shell, MALL_ERR, 0, NULL);
	if (arg[0] == '\"')
	{
		j = 1;
		if (arg[len - 1] == '\"')
			len--;
	}
	while (i < len && j < len && arg[j] != 0)
		ft_norm_clean_arg(arg, new, &i, &j);
	free(*str);
	*str = new;
}

void	ft_clean_cmd(t_shell *shell, char **cmd)
{
	char	*new;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = *cmd;
	new = ft_calloc(1, ft_strlen(str) + 1);
	if (new == NULL)
		ft_error(shell, MALL_ERR, 0, NULL);
	while (str != NULL && str[i] != 0)
	{
		if (str[i] == '\'' && ft_quotes(str, i) != 2)
			i++;
		else if (str[i] == '\"' && ft_quotes(str, i) != 1)
			i++;
		else if (!(str[i] == '\'' && str[i] == '\"'))
			new[j++] = str[i++];
		else
			i++;
	}
	*cmd = ft_strdup(new);
	free(str);
	free(new);
}
