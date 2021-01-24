/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/24 15:40:50 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char *get_com_name(char *line)
{
	char *name;
	
}

t_comand *get_next_comand(char **line, char **envs)
{
	t_comand *com;

	if (!(com = (t_comand *)ft_calloc(1, sizeof(t_comand))))
		return (0);
	*line = ft_skip_spaces(*line);
	com->name = get_com_name(line, envs);
	com->path_to_bin = get_path_to_bin(com->name, envs);
	*line = ft_skip_spaces(*line);
	com->argv = get_com_argv(line, envs);
	return (com);
}



// 1. Парсинг env в лист??? для удобства добавления и удаления.
// 2. Env до export??? флаг или отдельный лист
// 3. ; и | > < >> до и после пробелов может и не быть
// 4. ' и " непонятно что длеать
// echo kk>gg все хорошо, но если число вместо kk то появляется что-то с дескрпитором. echo sdfsdf 555>gg вывод: sdfsdf
// нет пробела между аргументами это один аргумент