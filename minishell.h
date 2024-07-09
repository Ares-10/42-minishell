/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:44 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/08 15:46:07 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>

# define SUCCESS 1
# define FAILURE 0

# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT 3
# define T_CMD 4
# define T_REDIRECTS 5
# define T_SIMPLECMD 6

/* > >> < << */
# define OUTPUT_REDIRECT 1
# define APPEND_REDIRECT 2
# define INPUT_REDIRECT 3
# define HERE_DOCUMENT 4

char	**g_envp;

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

typedef struct s_tree
{
	int				type;
	void			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_redirect
{
	int		type;
	char	*file_path;
}	t_redirect;

typedef struct s_simplecmd
{
	char	*file_path;
	char	**argv;
}	t_simplecmd;

void	set_signal(void);
void	start_shell(char **envp);

t_tree	*parse(char *str, char **envp);

/* error.c */
void	puterr_exit(char *msg);
void	*puterr(char *msg);
void	*xmalloc(int size);
void	*ckm(void *ptr);
void	search_tree(t_tree *node, char **env);

#endif