/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:40:28 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/17 22:06:44 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "../minishell.h"
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

int		ft_strcmp(const char *s1, const char *s2);

void	exec_argv(char *cmd, char **argv, char **env);
void	exec_tree(t_tree *node, char ***env, t_pipe *info);

void	builtin_echo(char **argv, char **env);
void	builtin_cd(char **argv, char **env);
void	builtin_pwd(char **env);
void	builtin_export(char **argv, char ***env, t_pipe *info);
void	builtin_unset(char **argv, char ***env);
void	builtin_env(char **argv, char **env);
void	builtin_exit(char **argv, char **env);

int		ft_setenv(char ***env, char *var);
char	*ft_getenv(char *name, char **env);

void	write_error(char *msg);
void	error_and_exit(char *msg);

void	free_double(char **var);


#endif