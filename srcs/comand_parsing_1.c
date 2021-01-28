/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_parsing_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/28 10:16:32 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		check_after(char **line, t_comand *com)
{
	if (**line == ';')
		(*line)++;
	else if (**line == '|')
	{
		com->pipe_after = 1;
		(*line)++;
		*line = ft_skip_spaces(*line);
		if (**line == '\0')
			com->message = get_unexpect_token_message('|');
	}
}

int			set_next_arg(char **line, char **envvar, t_comand *com)
{
	t_strs	*redir;
	int		*fd;

	if (isredirect(*line))
	{
		redir = **line == '>' ? &com->redir_out : &com->redir_in;
		fd = **line == '>' ? &com->fd_out : &com->fd_in;
		if (**line == '>')
			com->add_out = !ft_strncmp(*line, ">>", 2) ? 1 : 0;
		*line = com->add_out == 1 ? *line + 2 : *line + 1;
		*line = ft_skip_spaces(*line);
		if (set_arg_to_strs(line, envvar, redir) == KO)
			com->message = ft_strdup(MALLOC_ERROR);
		else if (ft_strlen(redir->arr[redir->i - 1]) == 0)
			if (**line != '\n' && isspecial(*line))
				com->message = get_unexpect_token_message(**line);
			else
				com->message = ft_strdup(REDIR_ERROR);
		else if (try_set_fd(redir, fd, com->add_out) == KO)
			com->message = get_errno_message(redir->arr[redir->i - 1]);
	}
	else if (set_arg_to_strs(line, envvar, &com->argv) == KO)
		com->message = ft_strdup(MALLOC_ERROR);
	return (com->message == 0 ? OK : KO);
}

int			check_before(char **line, t_comand *com)
{
	*line = ft_skip_spaces(*line);
	if (**line == ';')
		com->message = get_unexpect_token_message(';');
	else if (**line == '<' || **line == '>' || !ft_strncmp(*line, ">>", 2))
		com->message = ft_strdup(REDIR_ERROR);
	else if (**line == '|')
		com->message = get_unexpect_token_message('|');
	return (com->message == 0 ? OK : KO);
}

t_comand	*init_comand(void)
{
	t_comand	*com;

	if (!(com = (t_comand *)ft_calloc(1, sizeof(t_comand))))
		return (0);
	if (init_strs(&com->argv, ARGV_MARKER) == KO ||
		init_strs(&com->redir_in, REDIR_IN_MARKER) == KO ||
		init_strs(&com->redir_out, REDIR_UOT_MARKER) == KO)
	{
		free_comand(com);
		return (0);
	}
	return (com);
}

t_comand	*get_next_comand(char **line, char **envvar)
{
	t_comand	*com;

	if (!(com = init_comand()))
		return (0);
	if (check_before(line, com) == KO)
		return (com);
	while (**line && **line != '\n' && !iscomandend(**line))
	{
		*line = ft_skip_spaces(*line);
		if (set_next_arg(line, envvar, com) == KO)
			return (com);
	}
	check_after(line, com);
	return (com);
}
