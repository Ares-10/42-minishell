/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:46:18 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/17 22:34:29 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <stdint.h>

int	check_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (FALSE);
	while (*str && ft_isdigit(*str))
		str++;
	return (*str == '\0');
}

void	builtin_exit(char **argv, char **env, t_pipe *info)
{
	uint8_t	exit_code;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		write_error("minishell: exit: too many arguments\n");
		free(*env);
		*env = ft_strdup("?=1");
		return ;
	}
	exit_code = 0;
	if (argv[1] != NULL)
	{
		if (check_numeric(argv[1]))
			exit_code = (ft_atoi(argv[1]) % 256);
		else
		{
			exit_code = 255;
			write_error("minishell: exit: numeric argument required\n");
		}
	}
	free(*env);
	*env = ft_strdup("?=0");
	if (!info->next_pipe_exist && !info->prev_pipe_exist)
		exit(exit_code);
}
