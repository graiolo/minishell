/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prio_relist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:57:18 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/13 15:36:23 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static void	ft_add_null(t_token *node, t_token *tmp, t_token **list)
{
	node = ft_new_node(">", 8);
	node->next = tmp->next;
	tmp->next = node;
	tmp = node;
	node = ft_new_node("/dev/null", 11);
	node->next = tmp->next;
	tmp->next = node;
	ft_update_prev(*list);
}

static void	*ft_norm_extract_sub_list(t_token **list,
	t_token *start, t_token *stop)
{
	if (*list == NULL || start == NULL
		|| stop == NULL || start == stop)
		return (NULL);
	if (ft_strcmp(start->str, "cat") == 0)
	{
		free(start->str);
		start->str = ft_strdup("read");
	}
	return (list);
}

void	ft_extract_sub_list(t_token **list,
	t_token *start, t_token *stop)
{
	t_token	*e_start;
	t_token	*e_stop;
	t_token	*tmp;
	t_token	*node;

	if (ft_norm_extract_sub_list(list, start, stop) == NULL)
		return ;
	node = ft_new_node("&&", 4);
	tmp = stop;
	e_start = stop->prev;
	while (tmp->next != NULL && ft_is_types(tmp->next, "CRELB") != 1)
		tmp = tmp->next;
	e_stop = tmp;
	e_start->next = e_stop->next;
	e_stop->next = node;
	node->next = start;
	if (start->prev != NULL)
		start->prev->next = stop;
	if (start->prev == NULL)
		*list = stop;
	tmp = e_start->prev;
	if (ft_is_types(e_start, "P") == 1)
		ft_remove_node(list, e_start);
	ft_add_null(node, tmp, list);
}
