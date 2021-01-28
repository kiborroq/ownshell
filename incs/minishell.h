/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:59:31 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/28 10:34:03 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define KO -1
# define OK 1

# define IN_QOUTS 1

# define STRS_SIZE 25
# define BUFFER_SIZE 1000

# define ARGV_MARKER 1
# define REDIR_IN_MARKER 2
# define REDIR_UOT_MARKER 3

// # define PATH_MAX 1024

# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define REDIR_ERROR "minishell: syntax error near unexpected token 'newline'"
# define MALLOC_ERROR "malloc error"

typedef	struct	s_fds
{
	int			before_fd[2];
	int			after_fd[2];
	int			fd_in;
	int			fd_uot;
	int			save_fd_in;
	int			save_fd_uot;
	int			status_in;
	int			status_out;
}				t_fds;

typedef struct	s_strs
{
	char		**arr;
	int			i;
	int			size;
	int			marker;
}				t_strs;

typedef struct	s_comand
{
	t_strs		argv;
	t_strs		redir_in;
	t_strs		redir_out;
	int			fd_out;
	int			fd_in;
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
int				try_set_fd(t_strs *files, int *fd, int add_out);
void			check_after(char **line, t_comand *com);

/*
**parsing_getcontent.c - functions for $"'\ treating during comand parsing
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
**do_with_strs.c - functions for working with strs
*/

int				strs_size(char **strs);
void			free_strs(char **strs);
char			**realloc_strs(char **old_strs);
int				init_strs(t_strs *new, int marker);

/*
**error_message_treat.c - functions for error messages creation
*/

char			*get_unexpect_token_message(char c);
char			*get_errno_message(char *prefix);

/*
**utils.c - functions for minishell help
*/

char			*ft_strjoin_wrap(char *s1, char *s2);
char			**sort_az(char **envvar, int swaps, int i);
int				print_error(const char *s1, const char *s2, const char *s3);

/*
**process_envp.c - functions for enviroment variables treating
*/

char			*get_env(char **envvar, char *target_key, int mode);
int				get_env_index(char **envvar, char *target_key);
char			*get_env_key(char *env);
char			**read_envp(char **envp);
char			**realloc_envvar(char ***envvar_old);

/*
**exec_commands.c - functions for command execution (both builtin and external)
*/

int				run_command(char *pathname, char **argv, char ***envvar);
int				find_builtin(char *pathname);
char			*append_dir(char **pathname, char **envvar);

/*
**builtins1.c - builtin commands part1
*/

int				exec_echo(char *pathname, char **argv, char ***envvar);
int				exec_pwd(char *pathname, char **argv, char ***envvar);
int				exec_cd(char *pathname, char **argv, char ***envvar);

/*
**builtins2.c - builtin commands part 2
*/

int				exec_env(char *pathname, char **argv, char ***envvar);
int				exec_export(char *pathname, char **argv, char ***envvar);
int				exec_unset(char *pathname, char **argv, char ***envvar);
int				exec_exit(char *pathname, char **argv, char ***envvar);

/*
**pipes.c - functions to process pipes
*/

int				handle_pipe(t_comand *com, char ***envvar);


/*
**get_next_line.c - func that get every line in current fd
*/

int				get_next_line(int fd, char **line);

#endif
