/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2020/09/12 23:01:51 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define int g_env_num = 100;

// везде не хватает защиты от ошибок выделения памяти !

// выделение доп памяти под наш массив переменных окружения
char	**realloc_envvar(char ***envvar_old) //// or ENV_NUM 11000 - definitely sufficient
											//// but bad in terms of space complexity
{
	char	**envar_new;
	int		i;

	g_env_num += 100;
	i = 0;
	envvar = malloc(g_env_num * sizeof(char *));
	while ((*envvar_old)[i])
	{
		envvar_new[i] = ft_strdup((*envvar_old)[i]);
		free ((*envvar_old)[i++]);
	}
	free(*envvar_old);
	return(envvar_new);
}

// переносим исходный массив с переменными окружения в наш собственный массив
// изначальный размер массива - 100 элементов-строк
char	**read_envp(char **envp)
{
	char	**envvar;
	int		i;

	i = 0;
	envvar = ft_calloc(g_env_num * sizeof(char *));
	while(envp[i])
	{
		envvar[i] = ft_strdup(envp[i]);
		if (i++ = g_env_num - 1)
			envvar = realloc_envvar(&envvar);
	}
	return (envvar);
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

// получить значение или индекс переменной окружения по ключу / названию переменной
// режим 1 - значение, режим 2 - индекс (в виде нуль-терминированной строки)
char	*get_env(char **envvar, char *target_key, int mode)
{
	char	*current_key;
	char	*delimiter;
	int		i;
	int		env_not_found;

	env_not_found = 1;
	while (env_not_found && envvar[i])
	{
		delimiter = ft_strchr(envvar[i], '=');
		current_key = ft_substr(envvar[i], 0, delimiter - envvar[i]);
		if (!ft_strcmp(current_key, target_key))
			env_not_found = 0;
		free(current_key);
		i++;
	}
	if (env_not_found)
		return (NULL);
	return (mode == 1 ? delimiter + 1 : ft_itoa(i));
}

// strtrim ''  в  get_env?