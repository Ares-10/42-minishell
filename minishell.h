/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:44 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/30 21:50:43 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdlib.h>

# include <readline/readline.h>

/*
 * token
 */

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT 3
# define T_DOUBLE_QUOTES 4
# define T_SINGLE_QUOTES 5

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

typedef struct s_tree
{
	t_token	token;
	t_tree	*left;
	t_tree	*right;
}	t_tree;

#endif