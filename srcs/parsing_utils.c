/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/29 11:28:28 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		isprotect(char ch)
{
	if (ch == '\\' || ch == '\'' || ch == '"' || ch == '$')
		return (1);
	return (0);
}

int		isredirect(char *str)
{
	if (*str == '>' || *str == '<' || !ft_strncmp(str, ">>", 2))
		return (1);
	return (0);
}

int		iscomandend(char ch)
{
	if (ch == ';' || ch == '|')
		return (1);
	return (0);
}

int		isspecial(char *str)
{
	if (isredirect(str) || iscomandend(*str))
		return (1);
	else
		return (0);
}

void	free_comand(t_comand **com)
{
	if (*com)
	{
		free_strs((*com)->argv.arr);
		free_strs((*com)->redir_in.arr);
		free_strs((*com)->redir_out.arr);
		ft_freeptr((void **)&(*com)->message);
		(*com)->fd_in != STDIN_FILENO ? close((*com)->fd_in) : 0;
		(*com)->fd_out != STDOUT_FILENO ? close((*com)->fd_out) : 0;
		free(*com);
		*com = 0;
	}
}
