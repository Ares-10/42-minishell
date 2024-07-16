/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:46:18 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/16 16:50:55 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <stdint.h>

void	builtin_exit(char **argv)
{
	uint8_t	exit_code;

	write_error("exit\n");
	if (argv[1] != NULL && argv[2] != NULL)
	{
		write_error("minishell: exit: too many arguments");
		return ;
	}
	exit_code = 0;
	if (argv[1] != NULL)
		exit_code = (atoi(argv[1]) % 256);
	exit(exit_code);
}
