/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:11:38 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/04 16:07:18 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "minishell.h"

int	sig_echo_off(int in_fd)
{
	struct termios	tty;

	if (tcgetattr(in_fd, &tty) != 0)
		pexit("tcgetattr2 error");
	tty.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(in_fd, TCSANOW, &tty) != 0)
		pexit("tcsetattr");
	return (1);
}

int	sig_echo_on(int in_fd)
{
	struct termios	tty;

	if (tcgetattr(in_fd, &tty) != 0)
		pexit("tcgetattr error");
	tty.c_lflag |= ECHOCTL;
	if (tcsetattr(in_fd, TCSANOW, &tty) != 0)
		pexit("tcsetattr");
	return (1);
}

void	child_sig_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		dprintf(2, "are you there?");
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	else if (sig == SIGTERM)
		exit(0);
}
