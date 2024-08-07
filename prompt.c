/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:13:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/08/07 19:11:02 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "run.h"
#include <sys/ioctl.h>

int	is_white_space(char *str)
{
	int		i;

	if (str == NULL)
		return (1);
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

static void	init_exit_sig(char **env)
{
	if (g_sig == SIGINT)
	{
		free(*env);
		*env = ckm(ft_strdup("?=1"));
	}
	if (g_sig == SIGTERM)
	{
		free(*env);
		*env = ckm(ft_strdup("?=0"));
	}
	g_sig = 0;
}

static void	run(t_tree *tree, char ***envp)
{
	t_pipe	*info;

	init_pipe(&info);
	sig_echo_off(STDIN_FILENO);
	handle_heredoc(tree, *envp, info);
	if (g_sig == 0)
	{
		search_tree(tree, envp, info);
		wait_all_child(info, *envp);
	}
	restore_io(*info);
	sig_echo_off(STDIN_FILENO);
	free(info);
}

void	start_shell(char ***envp)
{
	char	*input;
	t_tree	*parse_tree;

	while (1)
	{
		input = readline("\033[0;32m[minishell] % \033[0m");
		if (!is_white_space(input))
		{
			add_history(input);
			init_exit_sig(*envp);
			parse_tree = parse(input, *envp);
			if (parse_tree != FAILURE)
				run(parse_tree, envp);
			set_signal();
			free_tree(&parse_tree);
			free(input);
		}
		else if (input == NULL)
		{
			ft_putstr_fd("\033[1A\033[14Cexit\n", 1);
			exit(0);
		}
	}
}
