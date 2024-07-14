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

void	run(t_tree **tree, char **envp)
{
	t_pipe	*info;

	init_pipe(&info);
	search_tree(*tree, envp, info);
	restore_io(*info);
}

void	start_shell(char **envp)
{
	char	*input;
	t_tree	*parse_tree;

	while (1)
	{
		input = readline("[minishell] % ");
		if (check_str(input))
		{
			add_history(input);
			parse_tree = parse(input, envp);
			run(&parse_tree, envp);
			// printf("You entered: %s\n", input);
		}
		else if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		free(input);
	}
}
