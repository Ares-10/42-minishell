/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:01:49 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/21 16:06:48 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static void	wait_heredoc(char **env)
{
	int	state;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(-1, &state, 0);
	state = WEXITSTATUS(state);
	if (state == 1)
	{
		free(*env);
		*env = ft_strdup("?=1");
	}
	else if (state == 0)
	{
		free(*env);
		*env = ft_strdup("?=0");
	}
	set_signal();
}

static void	get_line_heredoc(t_redirect *redirect, int tmp_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redirect->file_path) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc(t_redirect *redirect, char **env, t_pipe *info)
{
	char			*line;
	int				tmp_fd;
	struct termios	term;
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		pexit("fork failed");
	if (pid == 0)
	{
		init_term(info, &term, &line, &tmp_fd);
		get_line_heredoc(redirect, tmp_fd);
		restore_term(tmp_fd, &term, env);
		exit (0);
	}
	else
		wait_heredoc(env);
}
