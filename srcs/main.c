/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/02 14:39:35 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	exit_minishell(char *message)
{
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	free_comand(&g_shell.com);
	free_strs(g_shell.envvar);
	close(g_shell.save_fds[0]);
	close(g_shell.save_fds[1]);
	exit(g_shell.exit_status);
}

void	do_allcomands(char *line, char ***envvar, t_comand **com)
{
	int	pipe_before;

	pipe_before = 0;
	line = ft_skip_spaces(line);
	while (*line)
	{
		(*com) = get_next_comand(&line, *envvar);
		(*com)->pipe_before = pipe_before;
		pipe_before = (*com)->pipe_after;
		if (!(*com)->message || (*com)->pipe_after || (*com)->pipe_before)
			g_shell.exit_status = pipe_redir_run(*com, envvar);
		if ((*com)->message != 0)
			print_error((*com)->message, 0, 0);
		free_comand(com);
		g_shell.subshell = 0;
	}
}

void	get_nl_and_treat_eof(char **line)
{
	char	*save;
	int		status;
	size_t	len;

	save = 0;
	while ((status = get_next_line(STDIN_FILENO, line)) == 0)
	{
		len = ft_strlen(*line);
		if (len == 0 && save == 0)
			exit_minishell(EXIT_MESSAGE);
		if (len > 0)
			save = ft_strjoin_wrap(save, *line);
	}
	if (status == -1)
	{
		g_shell.exit_status = STDEXIT_CODE;
		exit_minishell(strerror(errno));
	}
	*line = ft_strjoin_wrap(save, *line);
}

void	init_minishell(char **envp)
{
	g_shell.com = 0;
	g_shell.exit_status = 0;
	g_shell.envvar = read_envp(envp);
	g_shell.save_fds[0] = dup(STDIN_FILENO);
	g_shell.save_fds[1] = dup(STDOUT_FILENO);
	g_shell.subshell = 0;
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, catch_sigquit);
	signal(SIGSEGV, catch_sigsegv);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	init_minishell(envp);
	while (1)
	{
		g_shell.pid = 0;
		print_prompt(g_shell.envvar);
		get_nl_and_treat_eof(&line);
		if (check_line(line, 0, 0) == OK)
			do_allcomands(line, &g_shell.envvar, &g_shell.com);
		ft_freeptr((void **)&line);
	}
	return (0);
}
