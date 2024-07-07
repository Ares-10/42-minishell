/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:15:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/07 19:46:15 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
}

/* safe */
static char	*get_env_value(char *name)
{
	int		i;
	char	*p;
	char	*env_value;

	i = -1;
	while (g_envp[++i] != NULL)
	{
		p = ft_strchr(g_envp[i], '=');
		if (p == NULL)
			continue ;
		if (ft_strncmp(name, g_envp[i], ft_strlen(name)) == 0
			&& g_envp[i][ft_strlen(name)] == '=')
		{
			env_value = ft_strdup(p + 1);
			if (env_value == NULL)
				puterr("malloc failed");
			return (env_value);
		}
	}
	env_value = ft_strdup("");
	if (env_value == NULL)
		puterr("malloc failed");
	return (env_value);
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
	{
		var_name[0] = '\0';
		return (FAILURE);
	}
	return (i + brace_flag);
}

/* safe */
static int	replace_var(char **str)
{
	char	*env_value;
	char	*var_name;
	int		var_len;
	char	*tmp;

	if (!(ft_isalnum((*str)[1]) || (*str)[1] == '_' || (*str)[1] == '{'))
		return (SUCCESS);
	var_name = (char *)xmalloc(ft_strlen(*str));
	var_len = get_var_name(*str, var_name);
	if (var_len == 0)
	{
		free(var_name);
		return (FAILURE);
	}
	env_value = get_env_value(var_name);
	free(var_name);
	tmp = *str;
	*str = ft_strjoin(env_value, *str + var_len);
	if (*str == NULL)
		puterr("malloc failed");
	free(tmp);
	free(env_value);
	return (SUCCESS);
}

/* safe */
char	*replace_variable(char *str)
{
	int		i;
	char	*new_str;
	char	**strs;
	char	*tmp;

	strs = var_split(str);
	i = 0;
	new_str = ckm(ft_strdup(strs[0]));
	while (strs[++i])
	{
		if (replace_var(&strs[i]) == FAILURE)
		{
			free_strs(strs);
			return (FAILURE);
		};
		tmp = new_str;
		new_str = ckm(ft_strjoin(new_str, strs[i]));
		free(tmp);
	}
	free_strs(strs);
	return (new_str);
}
