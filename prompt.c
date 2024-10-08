/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:13:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/08/11 16:40:20 by hyungcho         ###   ########.fr       */
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
	else if (g_sig == SIGTERM)
	{
		free(*env);
		*env = ckm(ft_strdup("?=0"));
	}
	else if (g_sig == SIGQUIT)
	{
		free(*env);
		*env = ckm(ft_strdup("?=131"));
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
	if (info->child_pids)
		free(info->child_pids);
	free(info);
}

void	start_shell(char ***envp)
{
	char	*input;
	t_tree	*parse_tree;

	while (1)
	{
		input = readline("[minishell] % ");
		if (!is_white_space(input))
		{
			add_history(input);
			init_exit_sig(*envp);
			parse_tree = parse(input, *envp);
			if (parse_tree != FAILURE)
				run(parse_tree, envp);
			set_signal();
			free_tree(&parse_tree);
		}
		else if (input == NULL)
		{
			ft_putstr_fd("\033[1A\033[14Cexit\n", 1);
			exit(0);
		}
		free(input);
	}
}
