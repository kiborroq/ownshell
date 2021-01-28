/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <kiborroq@kiborroq.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/27 11:27:57 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

extern int g_env_num;

int		exec_env(char *pathname, char **argv, char ***envvar)
{
	char	*key;
	int		i;

	if (argv[1])
		return (print_error(pathname, "too many arguments", 0));
	i = -1;
	while ((*envvar)[++i])
	{
		if (*get_env(*envvar, (key = get_env_key((*envvar)[i])), 1)
		|| !ft_strcmp(pathname, "export"))
			ft_putendl_fd((*envvar)[i], 1);
		free(key);
	}
	free(!ft_strcmp(pathname, "export") ? *envvar : NULL);
	return (0);
}

void	exec_export2(char ***envvar, char *argv_i, char *key)
{
	int		j;

	if ((j = get_env_index(*envvar, key)) < 0)
	{
		while ((*envvar)[++j])
			;
	}
	if (j == g_env_num - 2)
		*envvar = realloc_envvar(envvar);
	free((*envvar)[j]);
	(*envvar)[j] = ft_strjoin(argv_i, ft_strchr(argv_i, '=') ? "" : "=");
}

int		exec_export(char *pathname, char **argv, char ***envvar)
{
	char	**envvar_az;
	char	*key;
	int		exit_status;
	int		i;

	i = 0;
	exit_status = 0;
	if (!argv[i + 1])
	{
		envvar_az = sort_az(*envvar, 1, -1);
		return (exec_env(pathname, argv, &envvar_az));
	}
	while (argv[++i])
	{
		if (!ft_isalnum_str(key = get_env_key(argv[i])))
		{
			!exit_status ? print_error(pathname, "not valid in this context",
			key) : 0;
			exit_status += 1;
		}
		else
			exec_export2(envvar, argv[i], key);
		free(key);
	}
	return (exit_status > 0);
}

int		exec_unset(char *pathname, char **argv, char ***envvar)
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
		if ((j = get_env_index(*envvar, argv[i])) < 0)
		{
			if (!ft_isalnum_str(argv[i]) && !exit_status)
				print_error(pathname, argv[i], "invalid parameter name");
			exit_status += (!ft_isalnum_str(argv[i]) ? 1 : 0);
			continue ;
		}
		temp = (*envvar)[j--];
		while ((*envvar)[++j])
			(*envvar)[j] = (*envvar)[j + 1];
		free(temp);
	}
	return (exit_status > 0);
}

int		exec_exit(char *pathname, char **argv, char ***envvar)
{
	(void)pathname;
	(void)argv;
	(void)envvar;
	return (0);
}
