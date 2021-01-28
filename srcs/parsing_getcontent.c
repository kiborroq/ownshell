/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_getcontent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 18:08:41 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_1quots_content(char **line)
{
	int		i;
	char	*content;
	char	*begin;

	i = 0;
	begin = *line;
	while (**line && **line != '\'' && **line != '\n')
	{
		(*line)++;
		i++;
	}
	content = ft_strndup(begin, i);
	if (**line == '\'')
		(*line)++;
	return (content);
}

char	*get_mask_content(char **line, int type)
{
	char	*content;

	if (line[0][1] == '\n' || line[0][1] == '\0')
		content = ft_strdup("");
	else if (type == IN_QOUTS && (line[0][1] == '\'' || !isprotect(line[0][1])))
		content = ft_strndup(*line, 2);
	else
		content = ft_strndup(*line + 1, 1);
	*line = *line[1] == '\0' ? *line + 1 : *line + 2;
	return (content);
}

char	*get_other_content(char **line, int type)
{
	char	*content;
	char	*begin;

	begin = *line;
	if (type == IN_QOUTS)
		while (**line && **line != '\n' &&
				(**line == '\'' || !isprotect(**line)))
			(*line)++;
	else
		while (**line && !ft_isspace(**line) &&
				!isspecial(*line) && !isprotect(**line))
			(*line)++;
	content = ft_strndup(begin, *line - begin);
	return (content);
}

char	*get_env_content(char **line, char **envvar)
{
	char	*begin;
	char	*env_name;
	char	*content;

	begin = *line;
	while (ft_isalnum(**line) || **line == '_')
		(*line)++;
	if (*line > begin)
	{
		if (!(env_name = ft_strndup(begin, *line - begin)))
			return (0);
		content = get_env(envvar, env_name, 1);
		content = content == 0 ? ft_strdup("") : ft_strdup(content);
		free(env_name);
	}
	else if (**line == '?')
	{
		content = ft_itoa(0); // заменить на exit_code
		(*line)++;
	}
	else
		content = ft_strdup("$");
	return (content);
}

char	*get_2quots_content(char **line, char **envvar)
{
	char	*content;
	char	*arg;

	content = 0;
	while (**line && **line != '\n' && **line != '"')
	{
		if (!(arg = get_arg(line, envvar, IN_QOUTS)))
		{
			ft_freeptr((void **)&content);
			return (0);
		}
		if (!(content = ft_strjoin_wrap(content, arg)))
			return (0);
	}
	*line = **line == '"' ? *line + 1 : *line;
	return (content);
}
