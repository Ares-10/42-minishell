/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:23:19 by hyungcho          #+#    #+#             */
/*   Updated: 2024/08/11 03:47:30 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/* replvar.c */
char	*replace_variable(char *str, char **envp);

/* token.c */
void	tokenize(t_list **token_list, char *str);
void	delete_token(void *token);

/* tokenchecker.c */
int		token_check(t_list *token_list);

/* split.c */
char	**nquote_split(const char *str, char c);

/* utils.c */
int		check_quote(const char *str, int index);
void	free_strs(char ***strs);

/* treebuilder1,2 */
t_tree	*syntax_pipeline(t_list *token_list);
t_tree	*syntax_cmd(t_list *token_list);
t_tree	*syntax_redirects(t_list *token_list);
t_tree	*syntax_io_redirect(t_list *token_list);
t_tree	*syntax_simple_cmd(t_list *token_list);

#endif
