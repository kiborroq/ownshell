/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_getcontent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/30 12:02:51 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_1quots_content(char **line)
{
	int		i;
	char	*content;
	char	*begin;

	content = 0;
	i = 0;
	begin = *line;
	while (**line && **line != '\'')
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
	char	*curr;

	content = 0;
	curr = *line;
	if (curr[1] == '\0')
		content = ft_strdup("");
	else if (type == IN_QOUTS && (curr[1] == '\'' || !isprotect(line[0][1])))
		content = ft_strndup(curr, 2);
	else
		content = ft_strndup(curr + 1, 1);
	*line = curr[1] == '\0' ? curr + 1 : curr + 2;
	return (content);
}

char	*get_other_content(char **line, int type)
{
	char	*content;
	char	*begin;

	content = 0;
	begin = *line;
	if (type == IN_QOUTS)
		while (**line && (**line == '\'' || !isprotect(**line)))
			(*line)++;
	else
		while (**line && !ft_isspace(**line) &&
				!isspecial(*line) && !isprotect(**line))
			(*line)++;
	content = ft_strndup(begin, *line - begin);
	return (content);
}

char	*get_env_content(char **line, char **envvar, int type)
{
	char	*begin;
	char	*env_name;
	char	*content;

	content = 0;
	begin = *line;
	while (ft_isalnum(**line) || **line == '_')
		(*line)++;
	if (*line > begin)
	{
		env_name = ft_strndup(begin, *line - begin);
		content = get_env(envvar, env_name, 1);
		content = content == 0 ? 0 : ft_strdup(content);
		free(env_name);
	}
	else if (**line == '?')
	{
		content = ft_itoa(g_shell.exit_status);
		(*line)++;
	}
	else if (type == IN_QOUTS)
		content = ft_strdup("$");
	else if (*begin != '\'' && *begin != '"')
		content = ft_strdup("$");
	return (content);
}

char	*get_2quots_content(char **line, char **envvar)
{
	char	*content;
	char	*arg;

	content = 0;
	while (**line && **line != '"')
	{
		arg = get_arg(line, envvar, IN_QOUTS);
		content = ft_strjoin_wrap(content, arg);
	}
	*line = **line == '"' ? *line + 1 : *line;
	if (content == 0)
		content = ft_strdup("");
	return (content);
}
