/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/26 02:13:35 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**bubble_sort(char **envvar)
{
	int		swaps;
	char	*temp;
	int		i;

	swaps = 1;
	while (swaps)
	{
		i = 0;
		swaps = 0;
		while (envvar[i])
		{
			if (ft_strcmp(envvar[i], envvar[i + 1]) > 0)
			{
				temp = envvar[i];
				envvar[i] = envvar[i + 1];
				envvar[i++ + 1] = temp;
				swaps++;
			}
		}
	}
	return (envvar);
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
