/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/02/01 19:17:08 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

extern int g_env_num;

int		exec_env(char *pathname, char **argv, char ***envvar)
{
	char	*key;
	int		i;
	int		export;

	if (argv[1])
		return (print_error(pathname, "too many arguments", 0));
	i = -1;
	export = (!ft_strcmp(pathname, "export") ? 1 : 0);
	while ((*envvar)[++i])
	{
		if (*get_env(*envvar, (key = get_env_key((*envvar)[i])), 1)
		|| export)
		{
			export ? ft_putstr_fd("declare -x ", 1) : 0;
			ft_putendl_fd((*envvar)[i], 1);
		}
		free(key);
	}
	i = -1;
	while (export && (*envvar)[++i])
		free((*envvar)[i]);
	free(export ? *envvar : NULL);
	return (0);
}

int		check_key(char **key, int mode)
{
	int		i;

	i = -1;
	while ((*key)[++i])
	{
		if (!(((i != 0 && ft_isalnum((*key)[i]))
		|| ft_isalpha((*key)[i])) || (*key)[i] == '_'))
			break ;
	}
	if (mode == 1 && (*key)[i] == '+' && !(*key)[i + 1])
	{
		(*key)[i] = 0;
		return (2);
	}
	return (!(*key)[i]);
}

void	exec_export2(char ***envvar, char *argv_i, char *key, int mode)
{
	int		j;
	char	*value_joined;

	j = get_env_index(*envvar, key);
	if (j == g_env_num - 2)
		*envvar = realloc_envvar(envvar);
	value_joined = NULL;
	if (mode == 2)
		value_joined = ft_strjoin(j < 0 ? "" : get_env(*envvar, key, 1),
		ft_strchr(argv_i, '+') + 2);
	free((*envvar)[j]);
	(*envvar)[j] = ft_strjoin_three(key, "=", mode == 2 ? value_joined
	: argv_i + ft_strlen(key) + (strchr(argv_i, '=') != NULL));
	free(value_joined);
}

int		exec_export(char *pathname, char **argv, char ***envvar)
{
	char	**envvar_az;
	char	*key;
	int		exit_status;
	int		i;
	int		mode;

	i = 0;
	exit_status = 0;
	if (!argv[i + 1])
	{
		envvar_az = sort_az(*envvar, 1, -1);
		return (exec_env(pathname, argv, &envvar_az));
	}
	while (argv[++i])
	{
		key = get_env_key(argv[i]);
		if (!*key || !(mode = check_key(&key, 1)))
			exit_status = print_error(pathname, key,
			"not a valid identifier");
		else
			exec_export2(envvar, argv[i], key, mode);
		free(key);
	}
	return (exit_status);
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
		if (!(*envvar)[(j = get_env_index(*envvar, argv[i]))])
		{
			if (!check_key(&argv[i], 2))
				exit_status = print_error(pathname, argv[i],
				"invalid parameter name");
			continue ;
		}
		temp = (*envvar)[j--];
		while ((*envvar)[++j])
			(*envvar)[j] = (*envvar)[j + 1];
		free(temp);
	}
	return (exit_status);
}
