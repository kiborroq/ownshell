/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/02/01 19:11:00 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

extern int g_env_num;

int		exec_echo(char *pathname, char **argv, char ***envvar)
{
	int		i;
	int		j;
	int		newline;

	(void)pathname;
	(void)envvar;
	i = 0;
	newline = 1;
	while (argv[++i] && !ft_strncmp(argv[i], "-n", 2))
	{
		j = 1;
		while (argv[i][++j] == 'n')
			;
		if (argv[i][j])
			break ;
		newline = 0;
	}
	i--;
	while (argv[++i])
		ft_printf(argv[i + 1] ? "%s " : "%s", argv[i]);
	(!argv[1] || newline) ? ft_putchar_fd('\n', 1) : 0;
	return (0);
}

int		update_pwd_in_envvar(char ***envvar, char *newpwd, int mode)
{
	int		pwd;
	int		oldpwd;
	char	pwd_current[PATH_MAX];
	char	*temp;

	if (mode == 1 && !get_env(*envvar, "PWD", 1))
	{
		pwd = get_env_index(*envvar, "PWD");
		getcwd(pwd_current, PATH_MAX);
		(*envvar)[pwd] = ft_strjoin("PWD=", pwd_current);
	}
	else if (mode == 2)
	{
		oldpwd = get_env_index(*envvar, "OLDPWD");
		temp = (*envvar)[oldpwd];
		(*envvar)[oldpwd] = ft_strjoin("OLDPWD=", get_env(*envvar, "PWD", 1));
		free(temp);
		pwd = get_env_index(*envvar, "PWD");
		free((*envvar)[pwd]);
		(*envvar)[pwd] = ft_strjoin("PWD=", newpwd);
	}
	return (1);
}

int		exec_cd(char *pathname, char **argv, char ***envvar)
{
	int			ret;
	char		*cd;
	static char	*argv_pwd[2] = {"pwd", 0};
	char		path[PATH_MAX];
	char		*error;

	if (!argv[1] || !ft_strcmp(argv[1], "-"))
		cd = get_env(*envvar, !argv[1] ? "HOME" : "OLDPWD", 1);
	else
		cd = argv[1];
	if (!cd)
	{
		error = ft_strjoin(!argv[1] ? "HOME" : "OLDPWD", " not set");
		ret = print_error(pathname, error, 0);
		free(error);
	}
	else if (update_pwd_in_envvar(envvar, NULL, 1) && (ret = chdir(cd)))
		print_error(pathname, argv[1], strerror(errno));
	else
	{
		getcwd(path, PATH_MAX);
		update_pwd_in_envvar(envvar, path, 2);
	}
	return ((argv[1] && !ft_strcmp(argv[1], "-") && !ret) ?
	exec_pwd(pathname, argv_pwd, envvar) : ret < 0);
}

int		exec_pwd(char *pathname, char **argv, char ***envvar)
{
	char	path[PATH_MAX];

	(void)envvar;
	(void)argv;
	if (getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, 1);
		return (0);
	}
	return (print_error(pathname, strerror(errno), 0));
}

int		exec_exit(char *pathname, char **argv, char ***envvar)
{
	int		exit_status;

	(void)envvar;
	ft_putendl_fd("exit", 1);
	exit_status = argv[1] ? ft_atoi(argv[1]) : g_shell.exit_status;
	if (argv[1] && argv[2])
		exit_status = print_error(pathname, "too many arguments", 0);
	else if (argv[1] && !(ft_isdigit_str(argv[1]) ||
	(argv[1][0] == '-' && ft_isdigit_str(argv[1] + 1))))
		exit_status = 254 + print_error(pathname, argv[1],
		"numeric argument required");
	else if ((!exit_status || exit_status == -1) && argv[1]
	&& ft_strlen(argv[1]) > 2)
		exit_status = 254 + print_error(pathname, argv[1],
		"numeric argument required");
	else if (exit_status < 0 || exit_status > 255)
		exit_status %= 256 * (exit_status < 0 ? -1 : 1);
	g_shell.exit_status = exit_status;
	exit_minishell(NULL);
	return (0);
}
