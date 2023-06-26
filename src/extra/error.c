/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:30:21 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/16 19:10:18 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	*ft_error_line(char *name, char *value, char *error)
{
	char	*err;

	err = NULL;
	if (ft_strcmp(error, SYNTAX_ERR2) == 0)
	{
		err = ft_strjoin(name, error);
		err = ft_free_join(err, value, 1);
		err = ft_free_join(err, "'\n", 1);
		return (err);
	}
	if (ft_strcmp(error, CMD_ERR) == 0 && ft_strncmp(value, "./", 2) != 0)
		err = ft_strjoin(NULL, value);
	else
		err = ft_strjoin(name, value);
	if (ft_strlen(err) != ft_strlen(name))
		err = ft_free_join(err, ": ", 1);
	if (ft_strcmp(error, CMD_ERR) == 0 && ft_strncmp(value, "./", 2) == 0)
		err = ft_free_join(err, NO_FILE, 1);
	else
		err = ft_free_join(err, error, 1);
	if (ft_strlen(err) == ft_strlen(name))
		err[0] = 0;
	return (err);
}
