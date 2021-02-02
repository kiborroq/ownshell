/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_parsing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/01 19:24:27 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		try_set_fd(t_strs *files, int *fd, int add_out)
{
	if ((files->marker == REDIR_UOT_MARKER && *fd != STDOUT_FILENO) ||
		(files->marker == REDIR_IN_MARKER && *fd != STDIN_FILENO))
		close(*fd);
	if (files->marker == REDIR_UOT_MARKER && add_out == 1)
		*fd = open(files->arr[files->i - 1], O_CREAT | O_RDWR | O_APPEND,
										S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (files->marker == REDIR_UOT_MARKER && add_out == 0)
		*fd = open(files->arr[files->i - 1], O_CREAT | O_RDWR | O_TRUNC,
										S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		*fd = open(files->arr[files->i - 1], O_RDONLY);
	if (*fd < 0)
	{
		g_shell.exit_status = FD_CODE;
		return (KO);
	}
	return (OK);
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
		arg = get_env_content(line, envvar, type);
	}
	else if (**line == '\\')
		arg = get_mask_content(line, type);
	else
		arg = get_other_content(line, type);
	return (arg);
}

void	set_next_arg(char **line, char **envvar, t_strs *strs)
{
	char	*arg;

	arg = 0;
	*line = ft_skip_spaces(*line);
	while (**line && !ft_isspace(**line) && !isspecial(*line))
	{
		if (strs->i >= strs->size)
		{
			strs->arr = realloc_strs(strs->arr);
			strs->size *= 2;
		}
		if ((arg = get_arg(line, envvar, 0)) != 0)
		{
			arg = ft_strjoin_wrap(strs->arr[strs->i], arg);
			strs->arr[strs->i] = arg;
		}
	}
	if (strs->arr[strs->i] != 0)
		strs->i++;
}
