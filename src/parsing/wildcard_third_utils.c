/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_third_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:06:08 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/14 16:40:10 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

char	*ft_rm_asterix(char *str)
{
	char	*clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean = ft_calloc(ft_strlen(str) + 1, 1);
	while (str != NULL && str[i] != 0)
	{
		if (((str[i] != - '*') || (i && str[i - 1] != - '*'))
			|| (!i && str[i] == - '*'))
			clean[j++] = str[i];
		i++;
	}
	return (clean);
}

void	ft_correct_file(char **files, t_card cards, char **new)
{
	int		re;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (files != NULL && files[i] != NULL)
	{
		k = 0;
		re = 0;
		while (cards.card[k] != NULL)
		{
			if (cards.typo[k] == 1)
				re += ft_left_compare(files[i], cards.card[k]);
			else if (cards.typo[k] == 2)
				re += ft_right_compare(files[i], cards.card[k]);
			else if (cards.typo[k] == 3)
				re += ft_sub_str(files[i], cards.card[k]);
			k++;
			if (cards.card[k] == NULL && re == 0)
				new[j++] = ft_strdup(files[i]);
		}
		i++;
	}
}

char	**ft_get_name_files(char *file)
{
	char	**files;
	int		fd;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	files = ft_calloc(100, sizeof(char *));
	files[i] = get_next_line(fd);
	while (files[i++] != NULL)
		files[i] = get_next_line(fd);
	files[i] = NULL;
	close(fd);
	return (files);
}
