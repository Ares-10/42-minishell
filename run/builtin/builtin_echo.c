/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:24 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/16 16:48:37 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static int	check_if_option(char *str);

void	builtin_echo(char **argv, char **env)
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
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (need_newline)
		printf("\n");
	free(*env);
	*env = ckm(ft_strdup("?=0"));
}

static int	check_if_option(char *str)
{
	char	*tmp;

	tmp = str;
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
