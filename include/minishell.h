/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:44 by hyungcho          #+#    #+#             */
/*   Updated: 2024/08/06 18:18:22 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>

# define SUCCESS 1
# define FAILURE 0

# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT 3
# define T_CMD 4
# define T_REDIRECTS 5
# define T_SIMPLECMD 6

/* > >> < << */
# define OUTPUT_REDIRECT 1
# define APPEND_REDIRECT 2
# define INPUT_REDIRECT 3
# define HERE_DOC 4

int	g_sig;

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

typedef struct s_tree
{
	int				type;
	void			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_redirect
{
	int		type;
	int		heredoc_fd;
	char	*file_path;
}	t_redirect;

typedef struct s_simplecmd
{
	char	*file_path;
	char	**argv;
}	t_simplecmd;

typedef struct s_pipe
{
	int		prev_fd[2];
	int		prev_pipe_exist;
	int		next_pipe_exist;
	int		child_num;
	int		original_stdin;
	int		original_stdout;
	int		io_flag;
	pid_t	*child_pids;
}	t_pipe;

/* signal.c */
void	set_signal(void);

/* prompt.c */
void	start_shell(char ***envp);

/* parse/parse.c */
t_tree	*parse(char *str, char **envp);

/* error.c */
void	puterr_exit(char *msg);
void	*puterr(char *msg);
void	*xmalloc(int size);
void	*ckm(void *ptr);

/* treedestroyer.c */
void	free_tree(t_tree **tree);

/* run.c */
void	init_pipe(t_pipe **info);
void	search_tree(t_tree *node, char ***env, t_pipe *info);
void	restore_io(t_pipe info);
void	wait_all_child(t_pipe *info, char **env);

/* cursor.c */
void	get_cursor_position(int *rows, int *cols);

/* exec_heredoc.c */
void	search_heredoc(t_tree *node, int *flag);

#endif