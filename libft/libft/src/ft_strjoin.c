/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:54:55 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/17 00:04:47 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
	Allocates (with malloc(3)) and returns a new string, which is the result 
	of the concatenation of ’s1’ and ’s2’.

	RETURN VALUE
	The new string. NULL if the allocation fails.
*/

#include "../../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}

char	*ft_free_join(char *s1, char *s2, int flag)
{
	char	*str;

	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	if (flag == 1 && s1 != NULL)
		free(s1);
	else if (flag == 2 && s2 != NULL)
		free(s2);
	else if (flag == 3 && s1 != NULL && s2 != NULL)
	{
		free(s1);
		free(s2);
	}
	return (str);
}
