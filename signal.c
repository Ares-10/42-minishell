/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:53:58 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/19 16:22:54 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	else if (sig == SIGTERM)
		exit(0);
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
}

static void	child_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	else if (sig == SIGTERM)
		exit(0);
}

void	set_child_signal(void)
{
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
	signal(SIGTERM, child_sig_handler);
}