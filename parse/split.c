/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:07 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/06 19:49:52 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	**freeall(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

static int	word_count(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (s[++i])
		if ((s[i] == '$' && check_quote(s, i) != 1) || i == 0)
			count++;
	return (count);
}

static char	*get_word(char const *s, int i)
{
	int		len;

	len = 1;
	while (s[len + i]
		&& !(s[len + i] == '$' && check_quote(s, len + i) != 1))
		len++;
	return (ft_substr(s, i, len));
}

char	**var_split(char const *s)
{
	char	**strs;
	int		j;
	int		i;

	strs = (char **)malloc(sizeof(char *) * (word_count(s) + 1));
	if (strs == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		strs[j] = get_word(s, i);
		if (strs[j] == NULL)
			return (freeall(strs));
		i += ft_strlen(strs[j]);
		j++;
	}
	strs[j] = NULL;
	return (strs);
}