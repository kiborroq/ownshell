/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_with_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 01:54:11 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		strs_size(char **strs)
{
	int size;

	size = 0;
	while (strs[size])
		size++;
	return (size);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**realloc_strs(char **old_strs)
{
	char	**new_strs;
	int		i;
	int		size;

	i = 0;
	size = old_strs ? strs_size(old_strs) : 0;
	if (!(new_strs = ft_calloc(size * 2 + 1, sizeof(char *))))
	{
		free_strs(old_strs);
		return (0);
	}
	while (old_strs[i])
	{
		new_strs[i] = old_strs[i];
		i++;
	}
	free(old_strs);
	return (new_strs);
}

int		init_strs(t_strs *new)
{
	if (!(new->arr = (char **)ft_calloc(STRS_SIZE + 1, sizeof(char *))))
		return (KO);
	new->size = STRS_SIZE;
	return (OK);
}
