/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:19:09 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/07 19:26:12 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	put_declare_x(char **env);
int		valid_shell_name(char *name);

void	export_single(char *arg, int *err_flag, char ***env, t_pipe *info);
int		ft_setenv(char ***env, char *var);
void	change_env(char ***env, char *arg, int idx);
int		find_key_in_env(char *key, char **env);
void	ft_addenv(char *key, char *val, char ***env);

#endif