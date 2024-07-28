/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:22:11 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/28 18:59:19 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	remove_quote(char *str);
static int	get_token_size(const char *str);
t_token		*new_token(const char *str, int size);

void	tokenize(t_list **token_list, char *str)
{
	int		i;
	t_token	*token;
	int		size;
	t_list	*node;

	i = 0;
	*token_list = NULL;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] == '\0')
			break ;
		size = get_token_size(&str[i]);
		token = new_token(&str[i], size);
		node = ckm(ft_lstnew(token));
		ft_lstadd_back(token_list, node);
		i += size;
	}
}

t_token	*new_token(const char *str, int size)
{
	t_token	*token;

	token = (t_token *)xmalloc(sizeof(t_token));
	token->str = ckm(ft_substr(str, 0, size));
	remove_quote(token->str);
	if (str[0] == '<' || str[0] == '>')
		token->type = T_REDIRECT;
	else if (str[0] == '|')
		token->type = T_PIPE;
	else
		token->type = T_WORD;
	return (token);
}

int	get_token_size(const char *str)
{
	int	i;

	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (1);
	i = -1;
	while (str[++i])
	{
		if (check_quote(str, i) == 0
			&& (str[i] == ' ' || str[i] == '\t' || str[i] == '|'
				|| str[i] == '<' || str[i] == '>'))
			return (i);
	}
	return (i);
}

void	delete_token(void *token)
{
	free(((t_token *)token)->str);
	free(token);
}

void	remove_quote(char *str)
{
	int		i;
	int		new_index;
	char	*dup;

	dup = ckm(ft_strdup(str));
	i = -1;
	new_index = 0;
	while (dup[++i])
	{
		if (check_quote(dup, i) != -1)
		{
			str[new_index] = dup[i];
			new_index++;
		}
	}
	str[new_index] = '\0';
	free(dup);
}
