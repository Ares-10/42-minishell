/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:13:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/06 18:12:36 by hyungcho         ###   ########.fr       */
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

void	start_shell(void)
{
	char	*input;

	while (1)
	{
		input = readline("[minishell] % ");
		if (check_str(input))
		{
			add_history(input);
			parse(input);
			printf("You entered: %s\n", input);
		}
		else if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		free(input);
	}
}
