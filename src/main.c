/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graiolo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:13:51 by graiolo           #+#    #+#             */
/*   Updated: 2023/06/24 17:26:29 by graiolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	g_status;

static void	ft_init_shell(t_shell *shell)
{
	shell->path = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->status = 0;
}

static void	ft_norm_main(t_shell *shell, char *str)
{
	ft_init_shell(shell);
	ft_add_history(shell, str);
	shell->token = NULL;
	ft_get_token(shell, str);
	ft_read_tok(shell);
}

static void	ft_norm_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sig_init);
}

static int	ft_norm_invalid(char *str)
{
	if (ft_quotes(str, strlen(str)) != 0
		|| ft_slash(str, strlen(str)) != 0
		|| ft_brackets(str, strlen(str)) > 0)
	{
		printf("bash: invalid input\n");
		return (1);
	}
	if (ft_brackets(str, strlen(str)) < 0)
	{
		printf("bash: syntax error near unexpected token ')'\n");
		return (2);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	*line;
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		ft_error(shell, MALL_ERR, 0, NULL);
	shell->env = ft_get_env(env);
	ft_norm_signal();
	while (TRUE)
	{
		line = ft_read_line(argc, argv, shell);
		str = readline(line);
		add_history(str);
		free(line);
		if (str == NULL)
			break ;
		if (ft_norm_invalid(str) != 0)
			;
		else
			ft_norm_main(shell, str);
	}
	rl_clear_history();
	ft_sig_term(shell);
	return (0);
}
