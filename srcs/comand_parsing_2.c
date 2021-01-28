/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_parsing_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 18:07:28 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		try_set_fd(t_strs *files, int *fd, int add_out)
{
	if (*fd > 0)
		close(*fd);
	if (files->marker == REDIR_UOT_MARKER && add_out == 1)
		*fd = open(files->arr[files->i - 1], O_CREAT | O_RDWR | O_APPEND,
										S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (files->marker == REDIR_UOT_MARKER && add_out == 0)
		*fd = open(files->arr[files->i - 1], O_CREAT | O_RDWR | O_TRUNC,
										S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		*fd = open(files->arr[files->i - 1], O_RDONLY);
	return (*fd < 0 ? KO : OK);
}

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
