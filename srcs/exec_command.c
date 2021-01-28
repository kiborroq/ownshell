/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <kiborroq@kiborroq.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/26 10:19:10 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

extern int g_env_num;

int		find_builtin(char *pathname)
{
	static char	builtins[][7] = {"echo", "cd", "pwd",
				"export", "unset", "env", "exit"};
	int			i;

	i = -1;
	while (++i < 7)
	{
		if (!ft_strcmp(builtins[i], pathname))
			return (i);
	}
	return (-1);
}

char	*append_dir(char **pathname, char **envvar)
{
	char				**dirlist;
	char				*temp;
	int					i;
	int					file_not_found;
	static struct stat	statbuf[1];

	file_not_found = 1;
	dirlist = ft_split(get_env(envvar, "PATH", 1), ':');
	i = -1;
	while (file_not_found && dirlist[++i])
	{
		temp = ft_strjoin_three(dirlist[i], "/", *pathname);
		free(dirlist[i]);
		file_not_found = stat(temp, statbuf);
		free(file_not_found ? temp : NULL);
	}
	while (!file_not_found && dirlist[++i])
		free(dirlist[i]);
	free(dirlist);
	file_not_found ? print_error("minishell", "command not found",
	*pathname) : 0;
	free(*pathname);
	return (file_not_found ? NULL : temp);
}

int		run_command(char *pathname, char **argv, char ***envvar)
{
	static int		(*run_builtin[7])(char *pathname, char **argv,
					char ***envvar) = {exec_echo, exec_cd, exec_pwd,
					exec_export, exec_unset, exec_env, exec_exit};
	int				index;
	pid_t			pid;
	int				exit_status;

	exit_status = 127;
	if ((index = find_builtin(pathname)) >= 0)
		exit_status = run_builtin[index](pathname, argv, envvar);
	else if (ft_strchr(pathname, '/') || (pathname =
	append_dir(&pathname, *envvar)))
	{
		if (!(pid = fork()))
		{
			execve(pathname, argv, *envvar);
			print_error("minishell", strerror(errno), pathname);
			exit(1);
		}
		pid > 0 ? waitpid(pid, &exit_status, 0) :
		(exit_status = print_error("minishell", "fork failed", 0));
	}
	return (exit_status);
}
