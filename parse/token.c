/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:22:11 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/30 09:06:52 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	remove_quote(char *str);
static int	get_token_size(const char *str);
t_token		*new_token(const char *str, int size);

void	tokenize(t_list **token_list, char *str)
{
	int		i;
	t_token	*token;
	int		size;

	i = 0;
	*token_list = NULL;
	while (str[i])
	{
		while (str[i] && (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'))
			i++;
		size = get_token_size(&str[i]);
		token = new_token(&str[i], size);
		ft_lstadd_back(token_list, ft_lstnew(token));
		i += size;
	}
	if (check_quote(str, i))
		puterr("quote must be pair");
}

t_token	*new_token(const char *str, int size)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		puterr("malloc failed");
	token->str = ft_substr(str, 0, size);
	remove_quote(token->str);
	if (str[0] == '<' || str[0] == '>')
		token->type = REDIRECT;
	else if (str[0] == '|')
		token->type = PIPE;
	else
		token->type = WORD;
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
			&& (str[i] == ' ' || str[i] == '|'
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
	int	i;
	int	new_index;

	i = -1;
	new_index = 0;
	while (str[++i])
	{
		if (check_quote(str, i) != -1)
		{
			str[new_index] = str[i];
			new_index++;
		}
	}
	str[new_index] = '\0';
}
