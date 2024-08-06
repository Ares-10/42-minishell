/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:04:05 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/06 18:27:55 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "run.h"

void	count_heredoc(t_tree *node, int *total);
void	handle_heredoc(t_tree *node, char **envp, t_pipe *info);

void	exec_heredoc(t_redirect *redirect, char **envp, t_pipe *info);

#endif