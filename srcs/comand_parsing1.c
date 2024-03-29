/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_parsing1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/02 12:54:30 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		treat_commandend(char **line, t_comand *com)
{
	if (**line == ';')
		(*line)++;
	else if (**line == '|')
	{
		com->pipe_after = 1;
		(*line)++;
	}
}

void		redir_parsing(char **line, char **envvar, t_comand *com)
{
	t_strs	*redir;
	int		*fd;

	redir = **line == '>' ? &com->redir_out : &com->redir_in;
	fd = **line == '>' ? &com->fd_out : &com->fd_in;
	com->add_out = !ft_strncmp(*line, ">>", 2) ? 1 : 0;
	*line = com->add_out == 1 ? *line + 2 : *line + 1;
	*line = ft_skip_spaces(*line);
	set_next_arg(line, envvar, redir);
	if (try_set_fd(redir, fd, com->add_out) == KO)
	{
		com->message = get_errno_message(redir->arr[redir->i - 1]);
		while (**line && !iscomandend(**line))
			(*line)++;
		com->pipe_after = **line == '|' ? 1 : com->pipe_after;
		*line = iscomandend(**line) ? *line + 1 : *line;
	}
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
		free_comand(&com);
		return (0);
	}
	com->fd_in = STDIN_FILENO;
	com->fd_out = STDOUT_FILENO;
	return (com);
}

t_comand	*get_next_comand(char **line, char **envvar)
{
	t_comand	*com;

	if (!(com = init_comand()))
		return (0);
	while (**line && !iscomandend(**line))
	{
		*line = ft_skip_spaces(*line);
		if (isredirect(*line))
			redir_parsing(line, envvar, com);
		else
			set_next_arg(line, envvar, &com->argv);
		if (com->message)
			return (com);
	}
	treat_commandend(line, com);
	return (com);
}
