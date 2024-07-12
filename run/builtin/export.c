/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:41:30 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/12 13:14:22 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static void	change_env(char ***env, char *arg, int idx)
{
	// 원래 환경변수가 동적할당 된거 같지 않은데..
	// 환경변수를 그대로 복제해서 패스해준다고 가정해야겠다..
	// 그럼 free가 가능해지니까
	free((*env)[idx]);
	(*env)[idx] = ft_strdup(arg);
	if ((*env)[idx] == NULL)
		puterr_exit("malloc failed");
}

static int	add_env(char ***env, char *var)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	(*env)[i] = ft_strdup(var);
	(*env)[i + 1] = NULL;
	return (1);
}

static int	find_key_in_env(char *key, char **env)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while(env[i] != NULL)
	{
		if (ft_strncmp(key, env[i], key_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	builtin_export(char **argv, char ***env)
{
	int		i;
	int		idx;
	char	*equal;
	char	*key;

	if (argv[1] == NULL)
	{
		i = 0;
		while((*env)[i] != NULL)
		{
			printf("declare -x %s\n", (*env)[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		// export를 하려고 하는데, env내부에 있는 환경변수면, 그냥 
		// 그 값을 바꿔줘야 된다. 
		// 없으면 그냥 냅다 추가해버리고!
		// = 이 여러개 있어도 된다. 첫 =의 위치가 중요한데, 
		while(argv[i] != NULL)
		{
			// =가 없으면, 무시한다.
			printf("1\n");
			equal = ft_strchr(argv[i], '=');
			if (equal == 0)
				continue ;
			// =로 시작한다면 invalid 취급한다.
			if (equal == argv[i])
				printf("minishell: export: `%s': not a valid identifier\n", argv[i]);				
			// key가 있는 확인하자. : 찝찝한것: getenv를 써야될거 같아서.. 
			// 근데 그건, unistd.h 내부의 environ 전역변수에 접근해서 검색하는 로직이라, 
			// 전역변수를 시그널 말고는 사용할 수 없는 현재 서브젝트에는 적용이 불가능하다.
			key = ft_substr(argv[i], 0, equal - argv[i] + 1);
			if (key == NULL)
				puterr_exit("malloc failed");
			// key가 원래 환경변수목록에 있는지 확인한다. 있으면 index를 반환, 없으면 음수
			idx = find_key_in_env(key, *env);
			if (idx < 0)
				add_env(env, argv[i]);
			else
				change_env(env, argv[i], idx);
			i++;
		}
	}
}
