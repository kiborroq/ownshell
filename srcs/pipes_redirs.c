/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/02/01 21:22:35 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	parent_process(t_comand *com, int *old_fds, int *new_fds)
{
	if (com->pipe_before)
	{
		close(old_fds[0]);
		close(old_fds[1]);
	}
	if (com->pipe_after)
	{
		old_fds[0] = new_fds[0];
		old_fds[1] = new_fds[1];
	}
}

void	child_process(t_comand *com, char ***envvar, int *old_fds, int *new_fds)
{
	if (com->pipe_before)
	{
		if (com->fd_in == STDIN_FILENO && !com->message)
			dup2(old_fds[0], STDIN_FILENO);
		close(old_fds[0]);
		close(old_fds[1]);
	}
	if (com->pipe_after && !com->message)
	{
		if (com->fd_out == STDOUT_FILENO)
			dup2(new_fds[1], STDOUT_FILENO);
		close(new_fds[0]);
		close(new_fds[1]);
	}
	exit(com->message ? 2 :
	run_command(com->argv.arr[0], com->argv.arr, envvar));
}

int		handle_pipe2(t_comand *com, char ***envvar, pid_t *pid)
{
	static int	old_fds[2];
	static int	new_fds[2];

	if (com->pipe_after && !com->message)
		pipe(new_fds);
	if (!(*pid = fork()))
		child_process(com, envvar, old_fds, new_fds);
	else if (*pid > 0)
		parent_process(com, old_fds, new_fds);
	else if (*pid < 0)
		print_error("fork failed", 0, 0);
	return (1);
}

int		handle_pipe(t_comand *com, char ***envvar)
{
	static int		pcount = 0;
	static pid_t	pid[500];
	pid_t			i;
	int				exit_status;

	exit_status = 0;
	pcount += handle_pipe2(com, envvar, &pid[pcount]);
	if (!com->pipe_after || pcount == 500)
	{
		i = -1;
		while (++i < pcount)
			waitpid(pid[i], &exit_status, 0);
		exit_status /= (!(exit_status == 2 || exit_status == 3) ? 256 : 1);
		if (pcount == 500)
		{
			g_shell.exit_status = 128;
			print_error("fork failed", "Resource temporarily unavailable ", 0);
			exit_minishell(NULL);
		}
		pcount = 0;
	}
	return (exit_status);
}

int		pipe_redir_run(t_comand *com, char ***envvar)
{
	int	status;

	if (!com->message)
	{
		dup2(com->fd_in, STDIN_FILENO);
		dup2(com->fd_out, STDOUT_FILENO);
	}
	if (com->pipe_before || com->pipe_after)
		status = handle_pipe(com, envvar);
	else
		status = run_command(com->argv.arr[0], com->argv.arr, envvar);
	dup2(g_shell.save_fds[0], STDIN_FILENO);
	dup2(g_shell.save_fds[1], STDOUT_FILENO);
	return (status + (com->message ? 256 : 0));
}
