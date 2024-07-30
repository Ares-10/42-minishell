/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:40:28 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/31 00:04:44 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# define TRUE 1
# define FALSE 0
# define R 0
# define W 1
# define ERROR -1
# define FOUND 1
# define NOT_FOUND 0
# define BUF_SIZE 3
# define SAVE 0
# define LOAD 1
# define DULL 0

void	handle_pipe(t_tree *node, char ***env, t_pipe *info);
void	exec_heredoc(t_redirect *redirect, char **env, t_pipe *info);
void	handle_redirect(t_tree *node, char ***env, t_pipe *info);
void	handle_cmd(t_tree *node, char ***env, t_pipe *info);

int		ft_strcmp(const char *s1, const char *s2);

void	ft_execve(char *cmd, char **argv, char **env);

int		is_builtin(char *name);
int		exec_builtin(t_simplecmd *cmd, char ***env, t_pipe *info);
void	decode_waitpid(int *state);

int		builtin_echo(char **argv);
int		builtin_cd(char **argv, char ***env);
int		builtin_pwd(void);
int		builtin_export(char **argv, char ***env, t_pipe *info);
int		builtin_unset(char **argv, char ***env);
int		builtin_env(char **argv, char **env);
int		builtin_exit(char **argv, char **env);

int		ft_setenv(char ***env, char *var);
char	*ft_getenv(char *name, char **env);

void	pexit(char *msg);

void	ft_free(char **var);

void	init_term(t_pipe *info, struct termios *term);
void	restore_term(struct termios *term, char **env);

int		exec_builtin(t_simplecmd *cmd, char ***env, t_pipe *info);
void	wait_all_child(t_pipe *info, char **env);

void	child_sig_handler(int sig);
void	set_heredoc_signal(struct termios *term);
void	sig_echo_off(struct termios *term);
void	sig_echo_on(struct termios *term);

int		safe_dup(int fd);
void	safe_dup2(int f, int s);

void	save_load_io(int fd[2], int flag);

#endif