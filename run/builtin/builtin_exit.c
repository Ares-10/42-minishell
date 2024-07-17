/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:46:18 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/17 23:04:16 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <stdint.h>
#include <limits.h>

int ft_strtoll(const char *str, long long *out)
{
	long long	result;
	int			sign;
	int			digit;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = +1;
		str++;
	}
	result = 0;
	if (*str == '\0')
		return (ERROR);
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			digit = *str - '0';
			if (sign > 0 && (result > LLONG_MAX / 10 \
			|| (result == LLONG_MAX / 10 && digit > LLONG_MAX % 10)))
				return (ERROR);
			if (sign < 0 && (result > -(LLONG_MIN / 10) \
			|| (result == -(LLONG_MIN / 10) && digit > -(LLONG_MIN % 10))))
				return (ERROR);
			result = result * 10 + digit;
		}
		else
			return (ERROR);
		str++;
	}
	*out = result * sign;
	return (TRUE);
}

void	builtin_exit(char **argv, char **env, t_pipe *info)
{
	long long	input;
	uint8_t		exit_code;

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
		if (ft_strtoll(argv[1], &input) == TRUE)
			exit_code = (input % 256);
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
