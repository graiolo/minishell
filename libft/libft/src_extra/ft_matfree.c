/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:24:29 by iragusa           #+#    #+#             */
/*   Updated: 2023/06/14 16:58:29 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_free_mat(char **matrix)
{
	int	y;

	y = 0;
	if (matrix == NULL)
		return (0);
	while (matrix != NULL && matrix[y] != NULL)
	{
		free(matrix[y]);
		y++;
	}
	if (matrix != NULL)
		free(matrix);
	return (0);
}
