/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <kiborroq@kiborroq.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/26 02:13:35 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

extern int g_env_num;

char	**sort_az(char **envvar, int swaps, int i)
{
	char	**envvar_az;
	char	*temp;

	envvar_az = (char **)ft_calloc(g_env_num, sizeof(char *));
	while (envvar[++i])
		envvar_az[i] = ft_strdup(envvar[i]);
	while (swaps)
	{
		i = -1;
		swaps = 0;
		while (envvar_az[++i] && envvar_az[i + 1])
		{
			if (ft_strcmp(envvar_az[i], envvar_az[i + 1]) > 0)
			{
				temp = envvar_az[i];
				envvar_az[i] = envvar_az[i + 1];
				envvar_az[i + 1] = temp;
				swaps++;
			}
		}
	}
	return (envvar_az);
}

char	*ft_strjoin_wrap(char *s1, char *s2)
{
	char	*new;

	if (s1 == 0 && s2 == 0)
		new = 0;
	if (s1 == 0)
		new = s2;
	else if (s2 == 0)
		new = s1;
	else
	{
		new = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return (new);
}

int		print_error(const char *s1, const char *s2, const char *s3)
{
	ft_putstr_fd((char *)s1, 2);
	if (s2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)s2, 2);
	}
	if (s3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)s3, 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}
