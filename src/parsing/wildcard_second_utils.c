/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_second_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:03:40 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 15:18:04 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"

static void	first_child(t_shell *shell, t_pipex pipex, char *argv)
{
	char	*path;

	(void)argv;
	dup2(pipex.outfile, 1);
	path = ft_get_path_cmd(shell, "ls");
	pipex.cmd_args = ft_split(path, ' ');
	execve(path, pipex.cmd_args, NULL);
	ft_free_mat(pipex.cmd_args);
	free(path);
	ft_error(shell, NULL, 0, NULL);
}

static int	ft_norm_card_typo(t_card *cards, char *str, int *cp_i, int *cp_j)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cards->typo = ft_calloc(1024, sizeof(int *));
	if (str[0] != - '*')
	{
		while (str[i] != 0 && str[i] != - '*')
			i++;
		cards->typo[j] += 2;
		j++;
	}
	*cp_i = i;
	*cp_j = j;
	return (i);
}

static void	ft_card_typo(t_card *cards, char *str)
{
	char	*clean;
	int		i;
	int		k;
	int		j;

	clean = ft_rm_asterix(str);
	k = ft_norm_card_typo(cards, clean, &i, &j);
	while (clean != NULL && clean[i] != 0)
	{
		if (clean[i] == - '*')
		{
			if (k == i)
				cards->typo[j] += 1;
			else
				cards->typo[j] += 2;
		}
		if (cards->typo[j] == 3)
		{
			j++;
			k = i;
		}
		else
			i++;
	}
	free(clean);
}

char	**ft_card(t_shell *shell, char *str)
{
	t_pipex	pipex;
	t_card	cards;
	char	**files;
	char	**new;

	pipex.outfile = open(".壳", O_TRUNC | O_CREAT | O_RDWR, 0644);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(shell, pipex, str);
	waitpid(pipex.pid1, NULL, 0);
	files = ft_get_name_files(".壳");
	unlink(".壳");
	if (ft_strlen(str) == 1)
		return (files);
	cards.card = ft_split(str, - '*');
	ft_card_typo(&cards, str);
	new = ft_calloc(100, sizeof(char *));
	ft_correct_file(files, cards, new);
	free(cards.typo);
	ft_free_mat(cards.card);
	ft_free_mat(files);
	return (new);
}
