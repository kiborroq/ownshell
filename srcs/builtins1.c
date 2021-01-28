/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <kiborroq@kiborroq.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/26 10:19:36 by aronin           ###   ########.fr       */
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
	i = 1;
	newline = 1;
	while (argv[i] && argv[i][(j = 0)] == '-')
	{
		while (argv[i][++j] == 'n')
			;
		if (j > 1 && !argv[i++][j])
			newline = 0;
	}
	i--;
	while (argv[++i])
		ft_printf(argv[i + 1] ? "%s " : "%s", argv[i]);
	(!argv[1] || newline) ? ft_putchar_fd('\n', 1) : 0;
	return (0);
}

void	update_pwd_in_envvar(char ***envvar, char *newpwd)
{
	int		pwd;
	int		oldpwd;

	oldpwd = get_env_index(*envvar, "OLDPWD");
	free((*envvar)[oldpwd]);
	(*envvar)[oldpwd] = ft_strjoin("OLDPWD=", get_env(*envvar, "PWD", 1));	
	pwd = get_env_index(*envvar, "PWD");
	free((*envvar)[pwd]);
	(*envvar)[pwd] = ft_strjoin("PWD=", newpwd);
}

int		exec_cd(char *pathname, char **argv, char ***envvar)
{
	int			ret;
	char		*cd;
	static char	*argv_pwd[2]= {"pwd", 0};
	char		path[PATH_MAX];

	if (argv[1] && argv[2])
		return (print_error(pathname, "string not in pwd", argv[1]));
	if (!argv[1] || !ft_strcmp(argv[1], "-"))
		cd = get_env(*envvar, !argv[1] ? "HOME" : "OLDPWD", 1);
	else
		cd = argv[1];
	if ((ret = chdir(cd)))
		print_error(pathname, strerror(errno), argv[1]);
	else
	{
		getcwd(path, PATH_MAX);
		update_pwd_in_envvar(envvar, path);
	}
	return ((argv[1] && !ft_strcmp(argv[1], "-")) ? exec_pwd(pathname,
	argv_pwd, envvar) : ret < 0);
}

int		exec_pwd(char *pathname, char **argv, char ***envvar)
{
	char	path[PATH_MAX];

	(void)envvar;
	if (argv[1])
		print_error(pathname, "too many arguments", 0);
	else if (getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, 1);
		return (0);
	}
	else
		print_error(pathname, strerror(errno), 0);
	return (1);
}
