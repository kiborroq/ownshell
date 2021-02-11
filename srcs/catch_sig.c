/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/01 18:33:16 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	catch_sigint(int sign)
{
	(void)sign;
	if (!g_shell.pid && !g_shell.com)
	{
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		print_prompt(g_shell.envvar);
		g_shell.exit_status = 1;
	}
	else if (!g_shell.subshell)
		ft_putstr_fd("\n", STDERR_FILENO);
}

void	catch_sigquit(int sign)
{
	(void)sign;
	if (!g_shell.pid && !g_shell.com)
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
	else if (!g_shell.subshell)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

void	catch_sigsegv(int sign)
{
	(void)sign;
	g_shell.exit_status = SIGSEGV_CODE;
	exit_minishell(MALLOC_ERROR);
}
