/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/31 18:55:29 by aronin           ###   ########.fr       */
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

char	*append_dir(char *pathname, char **envvar)
{
	char				**dirlist;
	char				*temp;
	int					i;
	int					file_not_found;
	static struct stat	statbuf[1];

	file_not_found = 1;
	dirlist = ft_split(get_env(envvar, "PATH", 1), ':');
	i = -1;
	while (file_not_found && dirlist && dirlist[++i])
	{
		temp = ft_strjoin_three(dirlist[i], "/", pathname);
		free(dirlist[i]);
		file_not_found = stat(temp, statbuf);
		free(file_not_found ? temp : NULL);
	}
	while (!file_not_found && dirlist && dirlist[++i])
		free(dirlist[i]);
	free(dirlist);
	file_not_found ? print_error(pathname, "command not found", 0) : 0;
	return (file_not_found ? NULL : temp);
}

int		run_command(char *pathname, char **argv, char ***envvar)
{
	static int		(*run_builtin[7])(char *pathname, char **argv,
					char ***envvar) = {exec_echo, exec_cd, exec_pwd,
					exec_export, exec_unset, exec_env, exec_exit};
	int				index;
	int				exit_status;
	char			*pathname_wdir;

	exit_status = 127;
	if ((index = find_builtin(pathname)) >= 0)
		exit_status = run_builtin[index](pathname, argv, envvar);
	else if ((ft_strchr(pathname, '/') && !(pathname_wdir = NULL)) ||
	(pathname_wdir = append_dir(pathname, *envvar)))
	{
		if (!(g_shell.pid = fork()))
		{
			execve(pathname_wdir ? pathname_wdir : pathname, argv, *envvar);
			exit(print_error(strerror(errno), pathname, 0));
		}
		g_shell.pid > 0 ? waitpid(g_shell.pid, &exit_status, 0) :
		(exit_status = print_error("fork failed", 0, 0) + 255);
		exit_status /= (!(exit_status == 2 || exit_status == 3) ? 256 : 1);
		free(pathname_wdir);
	}
	return (exit_status + ((exit_status == 2 || exit_status == 3)
	? 128 : 0));
}
