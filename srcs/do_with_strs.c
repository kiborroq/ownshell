/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_with_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/29 10:00:47 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	print_strs(char **strs)
{
	while (*strs)
	{
		ft_printf("|%s|\n", *strs);
		strs++;
	}
}

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

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		ft_freeptr((void **)&strs[i]);
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
	size = old_strs ? strs_size(old_strs) * 2 + 1 : 0;
	if (!(new_strs = ft_calloc(size, sizeof(char *))))
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

int		init_strs(t_strs *new, int marker)
{
	if (!(new->arr = (char **)ft_calloc(STRS_SIZE + 1, sizeof(char *))))
		return (KO);
	new->size = STRS_SIZE;
	new->marker = marker;
	return (OK);
}
