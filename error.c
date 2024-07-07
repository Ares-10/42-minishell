/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 05:06:31 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/07 19:22:58 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check malloc */
void	*ckm(void *ptr)
{
	if (ptr == NULL)
		puterr("malloc failed");
	return (ptr);
}

/* safe */
void	*xmalloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		puterr("malloc failed");
	return (ptr);
}

void	puterr(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
