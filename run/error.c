/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:53:31 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/12 21:35:10 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	write_error(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

void	error_and_exit(char *msg)
{
	write_error(msg);
	exit(EXIT_FAILURE);
}