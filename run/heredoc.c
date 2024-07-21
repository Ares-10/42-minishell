/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:01:49 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/21 18:38:17 by seojepar         ###   ########.fr       */
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
	signal(SIGINT, do_sigint_heredoc);
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
		{
			ft_putstr_fd("\033[1A\033[2C", 1);
			break ;
		}
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
