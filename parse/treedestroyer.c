/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treedestroyer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:28:51 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/17 18:55:10 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_tree(t_tree **t)
{
	t_tree	*tree;
	char	**strs;
	int		i;

	tree = *t;
	if (tree == NULL)
		return ;
	free_tree(&tree->left);
	free_tree(&tree->right);
	if (tree->type == T_SIMPLECMD)
	{
		strs = ((t_simplecmd *)tree->data)->argv;
		i = -1;
		while (strs[++i])
			free(strs[i]);
		free(strs);
		free(((t_simplecmd *)tree->data)->file_path);
	}
	else if (tree->type == T_REDIRECT)
		free(((t_redirect *)tree->data)->file_path);
	free(tree->data);
	free(tree);
}