/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:40:28 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/07 22:35:38 by seojepar         ###   ########.fr       */
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

int		ft_strcmp(const char *s1, const char *s2);

void	exec_argv(char *cmd, char **env);

void	builtin_echo(char **argv);
void	builtin_cd(char **argv, char **env);
void	builtin_pwd(void);
void	builtin_export(char **argv, char ***env);
void	builtin_unset(char **argv, char ***env);
void	builtin_env(char **env);
void	builtin_exit(char **argv);

#endif