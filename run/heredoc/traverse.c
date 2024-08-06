/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:13:24 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/06 18:28:18 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

void	count_heredoc(t_tree *node, int *total)
{
	if (node->type == T_REDIRECT \
	&& ((t_redirect *)node->data)->type == HERE_DOC)
		(*total)++;
	if (node->left != NULL)
		count_heredoc(node->left, total);
	if (node->right != NULL)
		count_heredoc(node->right, total);
}

void	handle_heredoc(t_tree *node, char **envp, t_pipe *info)
{
	int	tmp;

	tmp = 0;
	count_heredoc(node, &tmp);
	if (tmp > 16)
	{
		ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
		exit (2);
	}
	if (node->type == T_REDIRECT \
	&& ((t_redirect *)node->data)->type == HERE_DOC)
		exec_heredoc(node->data, envp, info);
	if (node->left != NULL)
		handle_heredoc(node->left, envp, info);
	if (node->right != NULL)
		handle_heredoc(node->right, envp, info);
}
