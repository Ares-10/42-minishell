/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   run.c											  :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: seojepar <seojepar@student.42.fr>		  +#+  +:+	   +#+		      */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2024/06/24 21:29:55 by seojepar		  #+#	#+#			      */
/*   Updated: 2024/07/07 21:16:17 by seojepar		 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "run.h"

void	exec_tree(t_tree *node, char **env);
void	exec_command(t_tree *node, char **env);
void	handle_pipe(t_tree *node, char **env);
void	handle_redirect(t_tree *node, char **env);

void	search_tree(t_tree *node, char **env)
{
	exec_tree(node, env);
	if (node->left != NULL)
		search_tree(node->left, env);
	if (node->right != NULL)
		search_tree(node->right, env);
}

void	exec_tree(t_tree *node, char **env)
{
	if (node->type == T_WORD)
		exec_command(node->data, env);
	if (node->type == T_PIPE)
		handle_pipe(node, env);
	if (node->type == T_REDIRECT)
		handle_redirect(node, env);
}

void	handle_pipe(t_tree *node, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		exec_command(node->left, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
		exec_command(node->right, env);
		waitpid(pid, NULL, 0);
	}
}

void	handle_here_document(t_redirect *redirect, char **env)
{
	char	*line;
	int		tmp_fd;
	char	*tmp_filename;

	line = NULL;
	// tmp_filename = tmpnam(NULL);
	tmp_filename = ".tmp";
	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd < 0)
	{
		perror("Failed to open temporary file");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			break ;
		}
		if (strcmp(line, redirect->file_path) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open(tmp_filename, O_RDONLY);
	if (tmp_fd < 0)
	{
		perror("Failed to reopen temporary file");
		exit(EXIT_FAILURE);
	}
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	unlink(tmp_filename);
}

void	handle_redirect(t_tree *node, char **env)
{
	t_redirect	*redirect;
	int			fd;

	redirect = (t_redirect *)node->data;
	if (redirect->type == OUTPUT_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == APPEND_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == INPUT_REDIRECT)
		fd = open(redirect->file_path, O_RDONLY);
	else if (redirect->type == HERE_DOCUMENT)
	{
		handle_here_document(redirect, env);
		return ;
	}
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (redirect->type == OUTPUT_REDIRECT || redirect->type == APPEND_REDIRECT)
		dup2(fd, STDOUT_FILENO);
	else if (redirect->type == INPUT_REDIRECT)
		dup2(fd, STDIN_FILENO);
	close(fd);
	if (node->right)
		exec_command(node->right, env);
}
