/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:38:00 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/19 18:44:53 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	init_term(t_pipe *info, struct termios *term, char **line, int *tmp)
{
	char	*tmp_name;

	if (dup2(info->original_stdin, STDIN_FILENO) == -1)
		pexit("dup2 failed");
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	*line = NULL;
	tmp_name = ".tmp";
	*tmp = open(tmp_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp < 0)
		pexit("Failed to open temporary file");
}

void	restore_term(int tmp, struct termios *term, char **env)
{
	close(tmp);
	tmp = open(".tmp", O_RDONLY);
	if (tmp < 0)
		pexit("Failed to reopen temporary file");
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	unlink(".tmp");
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	free(*env);
	*env = ft_strdup("?=0");
}
