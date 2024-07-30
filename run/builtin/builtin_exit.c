/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:46:18 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 14:34:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <stdint.h>
#include <limits.h>

int	set_sign(char **str, int *sign, long long *result)
{
	*sign = +1;
	while (**str == ' ')
		(*str)++;
	if (**str == '-')
	{
		*sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	*result = 0;
	if (**str == '\0')
		return (ERROR);
	return (TRUE);
}

int	ft_strtoll(char *str, long long *out)
{
	long long	result;
	int			sign;
	int			digit;

	if (set_sign(&str, &sign, &result) == ERROR)
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

int	builtin_exit(char **argv, char **env)
{
	long long	input;
	uint8_t		exit_code;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(ft_getenv("?", env));
	if (argv[1] != NULL)
	{
		if (ft_strtoll(argv[1], &input) == TRUE)
			exit_code = (input % 256);
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit_code = 255;
		}
	}
	else
		exit_code = ft_atoi(ft_getenv("?", env));
	exit(exit_code);
}
