/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:44:33 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/24 15:30:24 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "errno.h"

typedef struct	s_comand
{
	t_list		*tmp_argv;
	char		*name;
	char		**argv;
	char		*path_to_bin;
	int			pipe_before;
	int			pipe_after;
}				t_comand;

#endif