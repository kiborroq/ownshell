/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:59:31 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 02:17:35 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "errno.h"
# include <stdio.h>

# define KO -1
# define OK 1

# define IN_QOUTS 1

# define STRS_SIZE 25

# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define REDIR_ERROR "minishell: syntax error near unexpected token 'newline'"
# define MALLOC_ERROR "malloc error"

typedef struct	s_strs
{
	char		**arr;
	int			i;
	int			size;
}				t_strs;

typedef struct	s_comand
{
	t_strs		argv;
	t_strs		redir_in;
	t_strs		redir_out;
	int			add_out;
	char		*pathname;
	int			pipe_before;
	int			pipe_after;
	char		*message;
}				t_comand;


/*
**comand_parsing_1.c and _2.c - structure of bash command parsing
*/

t_comand		*get_next_comand(char **line, char **envvar);
t_comand		*init_comand(void);
int				check_before(char **line, t_comand *com);
int				set_next_arg(char **line, char **envvar, t_comand *com);
int				set_arg_to_strs(char **line, char **envvar, t_strs *strs);
char			*get_arg(char **line, char **envvar, int type);
void			check_after(char **line, t_comand *com);

/*
**parsing_get_content.c - functions for $"'\ treating during comand parsing
*/

char			*get_2quots_content(char **line, char **envvar);
char			*get_1quots_content(char **line);
char			*get_mask_content(char **line, int type);
char			*get_env_content(char **line, char **envvar);
char			*get_other_content(char **line, int type);

/*
**parsing_utils.c - help functions for parsing
*/

int				isprotect(char ch);
int				isredirect(char *str);
int				iscomandend(char ch);
int				isspecial(char *str);
void			free_comand(t_comand *com);

/*
**do_with_strs.c - function for working with strs
*/

int				strs_size(char **strs);
void			free_strs(char **strs);
char			**realloc_strs(char **old_strs);
int				init_strs(t_strs *new);

/*
**error_message_treat.c - function for error messages creation
*/

char			*get_unexpect_token_message(char c);

/*
**utils.c - function for minishell help
*/

char			*ft_strjoin_wrap(char *s1, char *s2);
char			**bubble_sort(char **envvar);

/*
**envvar.c - function for enviroment variables treating
*/

char			*get_env(char **envvar, char *target_key, int mode);
char			**read_envp(char **envp);
int				get_env_index(char **envvar, char *target_key);
char			**realloc_envvar(char ***envvar_old); //можно заменить более абстрактной - realloc_strs, я писал для себя.

#endif
