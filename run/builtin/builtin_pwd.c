/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:46:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 14:35:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		pexit("pwd failed");
		return (1);
	}
}
