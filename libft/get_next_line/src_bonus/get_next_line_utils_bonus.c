/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:42:29 by graiolo           #+#    #+#             */
/*   Updated: 2023/04/20 20:29:27 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line_bonus.h"

void	ft_bzero(void *s, size_t len)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
}
