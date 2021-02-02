/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/02 15:11:51 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*skip_othercontent(char *line)
{
	while (*line && !iscomandend(*line) &&
			!isprotect(*line) && !isredirect(line))
		line++;
	return (line);
}

char	*skip_protectcontent(char *line)
{
	if (*line == '\\')
		line = line[1] ? line + 2 : line + 1;
	else if (*line == '\'')
	{
		line++;
		while (*line && *line != '\'')
			line++;
		line = *line == '\'' ? line + 1 : line;
	}
	else if (*line == '"')
	{
		line++;
		while (*line && *line != '"')
		{
			if (*line == '\\')
				line++;
			line = *line ? line + 1 : line;
		}
		line = *line == '"' ? line + 1 : line;
	}
	else
		line++;
	return (line);
}

int		check_line(char *line, int redir_before, int pipe_before)
{
	line = ft_skip_spaces(line);
	if (iscomandend(*line) || (redir_before && isredirect(line)))
		return (print_syntax_error(*line));
	if (pipe_before && *line == '\0')
		return (print_syntax_error('|'));
	if (redir_before && *line == '\0')
		return (print_syntax_error(0));
	if (*line == '\0')
		return (OK);
	while (*line && !iscomandend(*line) && !isredirect(line))
	{
		line = skip_protectcontent(line);
		line = skip_othercontent(line);
	}
	redir_before = isredirect(line);
	pipe_before = *line == '|' ? 1 : 0;
	line = *line ? line + 1 : line;
	line = *line && *line == '>' ? line + 1 : line;
	return (check_line(line, redir_before, pipe_before));
}
