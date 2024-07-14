/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:13:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/12 21:20:18 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	run(t_tree *tree, char **envp)
{
	t_pipe	*info;

	init_pipe(&info);
	search_tree(tree, envp, info);
	restore_io(*info);
}

static void	parse_and_run(char *input, char **envp)
{
	char	**strs;
	t_tree	*parse_tree;
	int		i;

	i = -1;
	strs = nquote_split(input, ';');
	while (strs[++i])
	{
		if (strs[i][0] == ';')
			parse_tree = parse(strs[i] + 1, envp);
		else
			parse_tree = parse(strs[i], envp);
		if (parse_tree == NULL)
			continue ;
		run(parse_tree, envp);
	}
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	start_shell(char **envp)
{
	char	*input;

	while (1)
	{
		input = readline("[minishell] % ");
		if (check_str(input))
		{
			add_history(input);
			parse_and_run(input, envp);
			free(input);
			// printf("You entered: %s\n", input);
		}
		else if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
	}
}
