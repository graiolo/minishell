/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:03:14 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/03 20:47:59 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static	void	ft_nsplit(char *s, const char c, size_t *n)
{
	size_t	i;

	i = 0;
	*n = 1;
	while (s != NULL && s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c && ft_quotes(s, i) != 2)
			(*n)++;
		i++;
	}
	if (s == NULL || !*s)
		*n = 0;
}

static	char	*ft_allocate(char **s_dest, char *s_sorg,
size_t *len, size_t *p)
{
	int	i;

	i = *p;
	(*p)++;
	s_dest[i] = (char *)malloc((*len + 1) * sizeof(char));
	if (!s_dest[i])
		return (NULL);
	ft_strncpy(s_dest[i], s_sorg - *len, *len);
	s_dest[i][*len] = 0;
	*len = 0;
	return (s_dest[i]);
}

char	**ft_shell_split(char *s, char c)
{
	size_t	n_of;
	char	**s_split;
	char	*s_sup;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	s_sup = s;
	ft_nsplit(s_sup, c, &n_of);
	s_split = (char **)ft_calloc((n_of + 1), sizeof(char *));
	while (s_split != NULL && s_sup != NULL && *s_sup)
	{
		if ((*s_sup != c && *s_sup) || ft_quotes(s, (s_sup - s)) != 0)
			len++;
		else if (len && *s_sup && ft_quotes(s, (s_sup - s)) != 2)
			ft_allocate(s_split, s_sup, &len, &i);
		s_sup++;
	}
	if (s != NULL && *s && *(s_sup - 1) != c)
		s_split[i] = ft_allocate(s_split, s_sup, &len, &i);
	if (s_split != NULL)
		s_split[i] = NULL;
	return (s_split);
}
