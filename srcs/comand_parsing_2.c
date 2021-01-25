/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_parsing_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 01:28:52 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_arg(char **line, char **envvar, int type)
{
	char	*arg;

	if (type != IN_QOUTS && **line == '"')
	{
		(*line)++;
		arg = get_2quots_content(line, envvar);
	}
	else if (type != IN_QOUTS && **line == '\'')
	{
		(*line)++;
		arg = get_1quots_content(line);
	}
	else if (**line == '$')
	{
		(*line)++;
		arg = get_env_content(line, envvar);
	}
	else if (**line == '\\')
		arg = get_mask_content(line, type);
	else
		arg = get_other_content(line, type);
	return (arg);
}

int		set_arg_to_strs(char **line, char **envvar, t_strs *strs)
{
	char	*arg;

	while (**line && !ft_isspace(**line) && !isspecial(*line))
	{
		if ((arg = get_arg(line, envvar, 0)) != 0)
		{
			arg = ft_strjoin_wrap(strs->arr[strs->i], arg);
			if (arg != 0 && strs->i >= strs->size)
			{
				if (!(strs->arr = realloc_strs(strs->arr)))
					return (KO);
				strs->size *= 2;
			}
			strs->arr[strs->i] = arg;
		}
		if (arg == 0)
			return (KO);
	}
	strs->i++;
	return (OK);
}
