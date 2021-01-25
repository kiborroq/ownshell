/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 00:59:17 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_2quots_content(char **line, char **envvar);

char	*get_env(char **envvar, char *target_key, int mode)
{
	char	*current_key;
	char	*delimiter;
	int		i;
	int		env_not_found;   

	env_not_found = 1;
	i = 0;
	while (env_not_found && envvar[i])
	{
		delimiter = ft_strchr(envvar[i], '=');
		current_key = ft_substr(envvar[i], 0, delimiter - envvar[i]);
		if (!ft_strcmp(current_key, target_key))
			env_not_found = 0;
		free(current_key);
		i++;
	}
	if (env_not_found)
		return (NULL);
	return (mode == 1 ? delimiter + 1 : ft_itoa(i - 1));
}

char	*get_unexpect_token_message(char c)
{
	char	*message;
	size_t	len;

	len = ft_strlen(UNEXPECTED_TOKEN);
	message = (char *)ft_calloc(len + 4, sizeof(char));
	if (message != 0)
	{
		ft_memcpy(message, UNEXPECTED_TOKEN, len);
		message[len + 0] = '\'';
		message[len + 1] = c;
		message[len + 2] = '\'';
	}
	return (message);
}

int		isprotect(char ch)
{
	if (ch == '\\' || ch == '\'' || ch == '"' || ch == '$')
		return (1);
	return (0);
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

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_comand(t_comand *com)
{
	free_strs(com->argv.arr);
	free_strs(com->redir_in.arr);
	free_strs(com->redir_out.arr);
	ft_freeptr((void **)&com->message);
	free(com);
}

char	**realloc_strs(char **old_strs) //// or ENV_NUM 11000 - definitely sufficient
											//// but bad in terms of space complexity
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
	return(new_strs);
}

int	isredirect(char *str)
{
	if (*str == '>' || *str == '<' || !ft_strncmp(str, ">>", 2))
		return (1);
	return (0);
}

int	iscomandend(char ch)
{
	if (ch == ';' || ch == '|')
		return (1);
	return (0);
}

int	isspecial(char *str)
{
	if (isredirect(str) || iscomandend(*str))
		return (1);
	else
		return (0);
}

char	*ft_strjoin_wrap(char *s1, char *s2)
{
	char	*new;

	if (s1 == 0 && s2 == 0)
		new = 0;
	if (s1 == 0)
		new = s2;
	else if (s2 == 0)
		new = s1;
	else
	{
		new = ft_strjoin(s1, s2);
		free(s1);
		free(s2);		
	}
	return (new);
}

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
	int		i;
	char	*content;
	char	*begin;

	i = 0;
	begin = *line;
	if (type == IN_QOUTS)
		while (**line && **line != '\n' &&
				(**line == '\'' || !isprotect(**line)))
		{
			(*line)++;
			i++;
		}
	else
		while (**line && !ft_isspace(**line) &&
				!isspecial(*line) && !isprotect(**line))
		{
			(*line)++;
			i++;
		}
	content = ft_strndup(begin, i);
	return (content);
}

char	*get_env_content(char **line, char **envvar)
{
	char	*begin;
	char	*env_name;
	char	*content;
	int		i;

	i = 0;
	begin = *line;
	while (ft_isalpha(**line) || **line == '_')
	{
		(*line)++;
		i++;
	}
	if (i > 0)
	{
		if (!(env_name = ft_strndup(begin, i)))
			return(0);
		content = get_env(envvar, env_name, 1);
		content = content == 0 ? ft_strdup("") : ft_strdup(content);
		free(env_name);
	}
	else
		content = ft_strdup("$");
	return (content);
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

int			set_arg_to_strs(char **line, char **envvar, t_strs *strs)
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

int init_strs(t_strs *new)
{
	if (!(new->arr = (char **)ft_calloc(STRS_SIZE + 1, sizeof(char *))))
		return (KO);
	new->size = STRS_SIZE;
	return (OK);
}

t_comand	*init_comand(void)
{
	t_comand	*com;

	if (!(com = (t_comand *)ft_calloc(1, sizeof(t_comand))))
		return (0);
	if (init_strs(&com->argv) == KO ||
		init_strs(&com->redir_in) == KO ||
		init_strs(&com->redir_out) == KO)
	{
		free_comand(com);
		return (0);
	}
	return (com);
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
	t_strs	*need;

	if (isredirect(*line))
	{
		need = **line == '>' ? &com->redir_out : &com->redir_in;
		com->add_out = !ft_strncmp(*line, ">>", 2) ? 1 : 0;
		*line = com->add_out == 1 ? *line + 2 : *line + 1;
		*line = ft_skip_spaces(*line);
		if (set_arg_to_strs(line, envvar, need) == KO)
			com->message = ft_strdup(MALLOC_ERROR);
		else if (ft_strlen(need->arr[need->i - 1]) == 0)
		{
			if (**line != '\n' && isspecial(*line))
				com->message = get_unexpect_token_message(**line);
			else
				com->message = ft_strdup(REDIR_ERROR);
		}
	}
	else if (set_arg_to_strs(line, envvar, &com->argv) == KO)
		com->message = ft_strdup(MALLOC_ERROR);
	return (com->message == 0 ? OK : KO);
}

void	print_strs(char **strs)
{
	while (*strs)
	{
		printf("|%s|\n", *strs);
		strs++;
	}
}

t_comand 	*get_next_comand(char **line, char **envvar)
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

int main(int argc, char **argv, char **envvar)
{
	t_comand *com;
	char	*line = "		echo  $USER	 '123''123'\"123\" \"$PATH ; | ' ' > >> < \\' \" > kk >> gg | cat < \"k\"'p't >> $KK; ";
	// char	*line = " \" k\\\\k \" ";
	(void)argc;
	(void)argv;
	while (*line != '\n' && *line)
	{
		com = get_next_comand(&line, envvar);
		// printf("argv:\n");
		// print_strs(com->argv.arr);

		// printf("redir_in:\n");
		// print_strs(com->redir_in.arr);

		// printf("redir_out:\n");
		// print_strs(com->redir_out.arr);

		// printf(">> ?: ");
		// printf("%d\n", com->add_out);

		// printf("pipe_after: ");
		// printf("%d\n", com->pipe_after);

		// printf("message: ");
		if (com->message)
		{
		// 	printf("%s\n", com->message);
			free_comand(com);
			return (0);
		}
		// else
		// 	printf("OK\n");
		// printf("\n");
		free_comand(com);
	}
	return 0;
}
