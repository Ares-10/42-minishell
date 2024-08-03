/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:58:39 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/03 22:04:19 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

int	safe_dup(int fd)
{
	int	ret;

	ret = dup(fd);
	if (ret == -1)
		pexit("dup failed");
	return (ret);
}

void	safe_dup2(int f, int s)
{
	if (dup2(f, s) == -1)
		pexit("dup2 failed");
	return ;
}

void	safe_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		pexit("pipe failed");
}
