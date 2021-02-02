/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_treat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/02 12:43:24 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

char	*get_errno_message(char *prefix)
{
	char	*message;
	char	*tmp;

	if (!(tmp = ft_strjoin(prefix, ": ")))
		return (0);
	message = ft_strjoin(tmp, strerror(errno));
	free(tmp);
	return (message);
}

int		print_error(const char *s1, const char *s2, const char *s3)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)s1, 2);
	if (s2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)s2, 2);
	}
	if (s3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char *)s3, 2);
	}
	ft_putstr_fd("\n", 2);
	return (1);
}

void	print_prompt(char **envvar)
{
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(get_env(envvar, "PWD", 1), STDERR_FILENO);
	ft_putstr_fd("$ ", STDERR_FILENO);
}

int		print_syntax_error(char token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(UNEXPECTED_TOKEN, STDERR_FILENO);
	if (token)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putchar_fd(token, STDERR_FILENO);
		ft_putchar_fd('`', STDERR_FILENO);
	}
	else
		ft_putstr_fd("`newline`", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_shell.exit_status = SYNTAX_CODE;
	return (KO);
}
