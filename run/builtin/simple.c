/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:24 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/13 18:04:43 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
int	check_if_option(char *str)
{
	char	*tmp = str;
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

void	builtin_echo(char **argv)
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
}

void	builtin_cd(char **argv, char **env)
{
	char	*msg;

	if (argv[1] == NULL)
		return ;
	if (chdir(argv[1]) == -1)
	{
		write_error("minishell: cd: ");
		perror(argv[1]);
	}
	// exit_status 추가 필요
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd failed");
}
