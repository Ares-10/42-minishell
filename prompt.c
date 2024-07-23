/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:13:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/23 15:51:41 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

int	check_str(char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (0);
	return (1);
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
	search_tree(tree, envp, info);
	restore_io(*info);
	free(info);
}

static void	exit_seq(int row, int col)
{
	printf("\033[%d;%dH%s\n", row - 1, col + 14, "exit");
	exit(0);
}

void	start_shell(char ***envp)
{
	char	*input;
	t_tree	*parse_tree;
	int		row;
	int		col;

	while (1)
	{
		get_cursor_position(&row, &col);
		input = readline("[minishell] % ");
		if (check_str(input))
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
			exit_seq(row, col);
	}
}
