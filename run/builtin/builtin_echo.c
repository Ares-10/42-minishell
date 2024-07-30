/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:24 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 17:40:35 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static int	check_if_option(char *str);

int	builtin_echo(char **argv)
{
	int	i;
	int	need_newline;

	i = 1;
	need_newline = TRUE;
	while (argv[i])
	{
		if (check_if_option(argv[i]))
			need_newline = FALSE;
		else
			break ;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (need_newline)
		ft_putstr_fd("\n", 1);
	return (0);
}

static int	check_if_option(char *str)
{
	if (*str != '-' || *(str + 1) == '\0')
		return (FALSE);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (FALSE);
		str++;
	}
	return (TRUE);
}
