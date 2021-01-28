/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/28 10:33:50 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int g_env_num = 100;

char	**realloc_envvar(char ***envvar_old)
{
	char	**envvar_new;
	int		i;

	g_env_num += 100;
	i = 0;
	envvar_new = malloc(g_env_num * sizeof(char *));
	while ((*envvar_old)[i])
	{
		envvar_new[i] = ft_strdup((*envvar_old)[i]);
		free((*envvar_old)[i++]);
	}
	free(*envvar_old);
	return (envvar_new);
}

char	**read_envp(char **envp)
{
	char	**envvar;
	int		i;

	i = -1;
	envvar = (char **)ft_calloc(g_env_num, sizeof(char *));
	while (envp[++i])
	{
		envvar[i] = ft_strdup(envp[i]);
		if (i == g_env_num - 2)
			envvar = realloc_envvar(&envvar);
	}
	return (envvar);
}

char	*get_env_key(char *env)
{
	char	*dlm;
	char	*key;

	dlm = ft_strchr(env, '=');
	key = ft_substr(env, 0, dlm ? (size_t)(dlm - env) : ft_strlen(env));
	return (key);
}

char	*get_env(char **envvar, char *target_key, int mode)
{
	char	*current_key;
	char	*delimiter;
	int		i;
	int		env_not_found;

	env_not_found = 1;
	i = -1;
	while (env_not_found && envvar[++i])
	{
		delimiter = ft_strchr(envvar[i], '=');
		current_key = ft_substr(envvar[i], 0, delimiter - envvar[i]);
		if (!ft_strcmp(current_key, target_key))
			env_not_found = 0;
		free(current_key);
	}
	if (env_not_found)
		return (NULL);
	return (mode == 1 ? delimiter + 1 : ft_itoa(i));
}

int		get_env_index(char **envvar, char *target_key)
{
	int		index;
	char	*index_str;

	if (!(index_str = get_env(envvar, target_key, 2)))
		return (-1);
	index = ft_atoi(index_str);
	free(index_str);
	return (index);
}
