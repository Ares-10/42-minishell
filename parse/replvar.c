/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:15:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/07 18:15:51 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*get_env_value(char *name)
{
	int		i;
	char	*p;

	i = -1;
	while (g_envp[++i] != NULL)
	{
		p = ft_strchr(g_envp[i], '=');
		if (p == NULL)
			continue ;
		if (ft_strncmp(name, g_envp[i], ft_strlen(name)) == 0
			&& g_envp[i][ft_strlen(name)] == '=')
			return (ft_strdup(p + 1));
	}
	return (ft_strdup(""));
}

static int	get_var_name(char *str, char *var_name)
{
	int		i;
	int		j;
	int		brace_flag;

	brace_flag = 0;
	if (str[1] == '{')
		brace_flag = 1;
	i = 1 + brace_flag;
	j = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		var_name[j++] = str[i++];
	var_name[j] = '\0';
	if (brace_flag && str[i] != '}')
		perror("parse error");
	return (i + brace_flag);
}

static void	replace_var(char **str)
{
	char	*env_value;
	char	*var_name;
	int		var_len;
	char	*tmp;

	if (!(ft_isalnum((*str)[1]) || (*str)[1] == '_' || (*str)[1] == '{'))
		return ;
	var_name = (char *)malloc(ft_strlen(*str));
	var_len = get_var_name(*str, var_name);
	env_value = get_env_value(var_name);
	free(var_name);
	if (env_value == NULL)
		return ;
	tmp = *str;
	*str = ft_strjoin(env_value, *str + var_len);
	free(tmp);
	free(env_value);
}

char	*replace_variable(char *str)
{
	int		i;
	char	*new_str;
	char	**strs;
	char	*tmp;

	strs = var_split(str);
	if (strs == NULL)
		return (NULL);
	i = 0;
	new_str = ft_strdup(strs[0]);
	while (strs[++i])
	{
		replace_var(&strs[i]);
		tmp = new_str;
		new_str = ft_strjoin(new_str, strs[i]);
		free(tmp);
	}
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	return (new_str);
}
