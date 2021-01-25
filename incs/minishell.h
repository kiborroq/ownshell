/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:44:33 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/25 20:23:33 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "errno.h"
# include <stdio.h>

# define KO -1
# define OK 1

# define IN_QOUTS 1

# define STRS_SIZE 25

# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define REDIR_ERROR "minishell: syntax error near unexpected token 'newline'"
# define MALLOC_ERROR "malloc error"

typedef struct	s_strs
{
	char		**arr;
	int			i;
	int			size;
}				t_strs;


typedef struct	s_comand
{
	t_strs		argv;
	t_strs		redir_in;
	t_strs		redir_out;
	int			add_out;
	char		*pathname;
	int			pipe_before;
	int			pipe_after;
	char		*message;
}				t_comand;

#endif