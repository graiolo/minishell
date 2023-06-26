/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:56:47 by graiolo           #+#    #+#             */
/*   Updated: 2023/05/11 23:57:48 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_realloc_str(void *ptr, size_t size)
{
	char	*new_ptr;

	if (ptr == NULL)
		return (ft_calloc(size + 1, 1));
	if (!size)
		return (ptr);
	new_ptr = (char *)ft_calloc(size + 1, 1);
	ft_strcpy((char *)new_ptr, (char *)ptr);
	free(ptr);
	return ((void *)new_ptr);
}
