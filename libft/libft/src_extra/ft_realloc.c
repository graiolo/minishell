/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:08:27 by graiolo           #+#    #+#             */
/*   Updated: 2023/05/11 21:49:29 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(size, 1);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		if (size < (size_t)malloc_usable_size(ptr))
			copy_size = size;
		else
			copy_size = (size_t)malloc_usable_size(ptr);
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}
