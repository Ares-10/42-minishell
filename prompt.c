/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:13:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/24 21:13:17 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_shell(void)
{
	char	*input;

	while (1)
	{
		input = readline("[minishell] % ");
		if (input)
		{
			add_history(input);
			printf("You entered: %s\n", input);
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		free(input);
	}
}
