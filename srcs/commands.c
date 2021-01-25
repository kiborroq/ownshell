/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2020/09/12 23:01:51 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>

#define PATH_MAX 1024 ///// limits.h ? MAXPATHLEN sys/params.h

int		exec_echo(char *pathname, char **argv, char **envvar)
{
	int		i;
	int		newline;

	(void)pathname;
	(void)envvar;
	newline = (ft_strcmp(argv[0], "-n") ? 1 : 0);
	i = (newline ? 0 : 1):
	while (argv[i])
		ft_printf("%s ", argv[i++]);
	newline ? ft_printf("\n") : 0;
	return (0);
}

int		exec_cd(char *pathname, char **argv, char **envvar)
{
	char	**location;
	char	*temp;
	char	*pwd;
	int		i;
	
	if (argv[2])
	{
		printf("cd: string not pwd: %s\n", argv[1]);
		return (1);
	}
	location = ft_split(argv[1], '/');
	// special case for empty arg - get env var HOME

	//replacing dot and dot-dot
	while (location[i])
	{
		if (!ft_strcmp(location[i], ".") || !ft_strcmp(location[i], ".."))
		{
			pwd = get_env(envvar, "PWD", 1);
			temp = location[i];
			location[i] = (ft_strlen(location[i] == 1) ?
			pwd : ft_substr(pwd, 0, ft_strrchr(pwd, '/') - pwd);
			free(temp);
		}
		
		i++;
	}

	//checking whether path is absolute or relative
}

int		exec_pwd(char *pathname, char **argv, char **envvar)
{
	char	path[PATH_MAX + 1];

	(void)pathname;
	(void)envvar;
	if (argv[1])
		ft_printf("pwd: too many arguments\n");
	else if (getcwd(path, PATH_MAX + 1))
	{
		ft_printf("%s\n", path);
		return (0);
	}
	return (1);
}

int		exec_export(char *pathname, char **argv, char **envvar)
{
	char	*key;
	char	*delimiter;
	int		exit_status;
	int		i;
	int		j;

	(void)pathname;
	i = 1;
	if (!argv[i])
		return (exec_env(pathname, argv, bubble_sort(envvar)));
	while (argv[i])
	{
		delimiter = ft_strchr(envvar[i], '=');
		if (!ft_isalnum(key = ft_substr(envvar[i], 0, delimiter ?
		delimiter - envvar[i] : ft_strlen(argv[i])))
			/// printf error
			exit status += 1;
		else
		{
			if ((j = get_env_index(envvar, key)) < 0)
				while (envvar[++j]) { ;}
			if (j = g_env_num - 1)
				envvar = realloc_envvar(&envvar);
			free(envvar[j]);
			envvar[j] = ft_strjoin(argv[i], delimiter ? "" : "=''");
			/////////////single quotes '' if spec chars
		}
		free(key);
	}
	return (exit_status > 0);
}

int		exec_unset(char *pathname, char **argv, char **envvar)
{
	char	*temp;
	int		exit_status;
	int		i;
	int		j;

	(void)pathname;
	i = 0;
	exit_status = 0;
	while (argv[++i])
	{
		if((j = get_env_index(envvar, argv[i], 2)) < 0)
		{
			if (!ft_isalnum(argv[i]) && !exit_status)
				printf("unset: %s: invalid parameter name\n", argv[i]);
			exit_status += (!ft_isalnum(argv[i]) ? 1 : 0);
			continue ;
		}
		temp = envar[j];
		while (envvar[j])
			envvar[j] = envvar[j++ + 1];
		free(temp);
	}
	return (exit_status > 0);
}

int		exec_env(char *pathname, char **argv, char **envvar)
{
	int		i;

	(void)pathname;
	(void)argv;
	i = 0;
	while (envvar[i])
		ft_printf("%s\n", envvar[i++]);
	return (0);
}

int		exec_exit(char *pathname, char **argv, char **envvar)
{

}

// ищем индекс в массиве с нашими командами, если не найден - возврат -1
void	find_builtin(char *pathname)
{
	static char	builtins[][7] = {"echo", "cd", "pwd",
				"export", "unset", "env", "exit"};
	int			i;
	char		*filename;

	i = 0;
	if ((filename = ft_strrchr(pathname, '/'))
		filename++;
	else
		filename = pathname;
	while (i < 7)
	{
		if (!ft_strcmp(builtins[i++], filename))
			return (i);
	}
	return (-1);
}

// ищем в переменной окружения PATH подходящий путь к executable
// для кейсов, когда пользователь ввел только название команды
void	append_dir_if_none(char **pathname, char **envvar)
{
	char		**dirlist;
	char		*temp;
	int			i;
	int			file_not_found;
	struct stat	*statbuf;

	if (ft_strchr(*pathname, '/'))
		return ;
	file_not_found = 1;
	dirlist = ft_split(get_env(envvar, "PATH", 1), ':');
	while (file_not_found && dirlist[i])
	{
		file_not_found = stat((temp = ft_strjoin(dirlist[i], *pathname)),
		statbuf);
		free(dirlist[i]);
		if (!file_not_found)
		{
			free(*pathname);
			*pathname = temp;
		}
		free(temp);
	}
	free(dirlist);
}

// функция-координатор для вызова нужной команды
// самописные команды пока вызываются в текущем процессе
int		run_command(char *pathname, char **argv, char **envvar)
{
	static int	(*run_builtin[7])(char *pathname, char **argv,
				char **envvar) = {exec_echo, exec_cd, exec_pwd,
				exec_export, exec_unset, exec_env, exec_exit};
	int			index;
	pid_t		pid;
	int			exit_status;

	if ((index = find_builtin(pathname)) >= 0)
		exit_status = run_builtin[index](pathname, argv, envvar);
	else
	{
		pid = fork();
		if (!pid)											/* child process*/
		{
			execve(append_dir_if_none(&pathname, envvar),
			argv, envvar));
			// printf errror
			exit(127);
		}
		else if (pid > 0) 									/* parent process*/
			wait(&exit_status); /// how to handle errors
		else 												/* fork error*/
			////////printf error
	}
	return (exit_status);
}
