/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everonel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:27:00 by graiolo           #+#    #+#             */
/*   Updated: 2023/11/30 22:29:56 by everonel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static void	ft_norm_init(t_token **cmd, t_token **red, t_token **new)
{
	*cmd = NULL;
	*red = NULL;
	*new = NULL;
}

void	ft_find_redir(t_shell *shell)
{
	t_token	*cmd;
	t_token	*red;
	t_token	*tmp;
	t_token	*new;

	ft_norm_init(&cmd, &red, &new);
	tmp = shell->token;
	while (tmp != NULL)
	{
		if (ft_is_types(tmp, "T") == 1)
			if (ft_add_back(&cmd, tmp->str) == NULL)
				ft_error(shell, MALL_ERR, 0, NULL);
		if (ft_is_types(tmp, " DXLB") == 1)
			if (ft_add_back(&cmd, tmp->str) == NULL)
				ft_error(shell, MALL_ERR, 0, NULL);
		if (ft_is_types(tmp, "WIOAH") == 1) {
			if (tmp->prev->type != IAPPEND && ft_add_back(&red, tmp->str) == NULL)
				ft_error(shell, MALL_ERR, 0, NULL);
			if (tmp->prev->type == IAPPEND && ft_add_back(&cmd, tmp->str) == NULL)
				ft_error(shell, MALL_ERR, 0, NULL);
		}
		if (tmp->next == NULL || ft_is_types(tmp->next, "PERC") == 1)
			ft_join_list(&cmd, &red, &new);
		if (ft_is_types(tmp, "PERC") == 1)
			if (ft_add_back(&new, tmp->str) == NULL)
				ft_error(shell, MALL_ERR, 0, NULL);
		tmp = tmp->next;
	}
	ft_free_list(&shell->token);
	shell->token = new;
	ft_update_prev(shell->token);
}

static void	ft_char_cmd(t_token *token)
{
	int	i;

	while (token != NULL)
	{
		i = 0;
		while (token->str != NULL && token->str[i] != 0)
		{
			if (ft_quotes(token->str, i) != 0
				&& ft_strchr("<>|;&()", token->str[i]))
				token->str[i] = -token->str[i];
			i++;
		}
		token = token->next;
	}
}

static void	ft_char_cmd_rvs(t_token *token)
{
	int	i;

	while (token != NULL)
	{
		i = -1;
		while (token->str != NULL && token->str[++i] != 0)
			if (token->str[i] < 0)
				token->str[i] = -token->str[i];
		token = token->next;
	}
}

void ft_set_heredoc_at_begin(t_shell *shell) {
	t_token *tmp = shell->token;
	t_token *start = shell->token;
	t_token *stop = NULL;
	t_token *target = NULL;

	while (tmp != NULL) {
		if (tmp->type == IAPPEND)
			target = tmp;
		if (ft_is_types(tmp, "PERC") == 1) {
			if (target != NULL && start != target) {
				ft_rotate_list(&shell->token, start, stop, target);
			}
			target = NULL;
			start = tmp->next;
		}
		stop = tmp;
		tmp = tmp->next;
	}
	if (target != NULL && start != target)
		ft_rotate_list(&shell->token, start, stop, target);
}

void	ft_get_token(t_shell *shell, char *str)
{
	int		i;
	char	*line;
	char	**mat;

	i = 0;
	if (str == NULL)
		return ;
	line = ft_line_space(str);
	free(str);
	str = ft_correct_form(line);
	free(line);
	mat = ft_shell_split(str, ' ');
	free(str);
	while (mat != NULL && mat[i] != NULL)
		if (ft_add_back(&shell->token, mat[i++]) == NULL)
			ft_error(shell, MALL_ERR, 0, NULL);
	ft_free_mat(mat);
	ft_char_cmd(shell->token);
	ft_clean_type(shell, shell->token);
	ft_set_heredoc_at_begin(shell);
	ft_heredoc(shell);
	ft_find_redir(shell);
	ft_char_cmd_rvs(shell->token);
	ft_operator(shell, shell->token);
	ft_prio(shell);
	ft_clean_null_cmd(shell->token);
	//ft_printf_list(shell->token);
}
