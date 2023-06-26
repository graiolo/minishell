/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_na_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:17:08 by graiolo           #+#    #+#             */
/*   Updated: 2023/05/16 16:26:34 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static	int	ft_get_len(int n)
{
	int	len;

	len = 0;
	if (!n)
		return (1);
	if (n < 0)
		++len;
	while (n != 0)
	{
		++len;
		n = n / 10;
	}
	return (len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa_no_malloc(int n)
{
	int			len;
	static char	s_out[5];

	len = ft_get_len(n);
	s_out[len] = '\0';
	if (n < 0)
		s_out[0] = '-';
	else if (n == 0)
		s_out[0] = '0';
	while (n != 0)
	{
		--len;
		s_out[len] = ft_abs((n % 10)) + '0';
		n /= 10;
	}
	return (s_out);
}
