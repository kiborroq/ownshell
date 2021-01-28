/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <kiborroq@kiborroq.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:34:57 by aronin            #+#    #+#             */
/*   Updated: 2021/01/26 10:19:44 by aronin           ###   ########.fr       */
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
		dup2(old_fds[0], 0);
		close(old_fds[0]);
		close(old_fds[1]);
	}
	if (com->pipe_after)
	{
		close(new_fds[0]);
		dup2(new_fds[1], 1);
		close(new_fds[1]);
		exit(run_command(com->argv.arr[0], com->argv.arr, envvar));
	}
	exit(0);
}

int		handle_pipe2(t_comand *com, char ***envvar, pid_t *pid)
{
	static int	old_fds[2];
	static int	new_fds[2];

	if (com->pipe_after)
		pipe(new_fds);
	if (!(*pid = fork()))
		child_process(com, envvar, old_fds, new_fds);
	else if (*pid > 0)
		parent_process(com, old_fds, new_fds);
	else if (*pid < 0)
		print_error("minishell", "fork failed", 0);
	return (1);
}

int		handle_pipe(t_comand *com, char ***envvar)
{
	static int		pcount = 0;
	static pid_t	pid[100];
	pid_t			i;
	int				exit_status;

	exit_status = 0;
	pcount += handle_pipe2(com, envvar, &pid[pcount]);
	if (!com->pipe_after)
	{
		exit_status = run_command(com->argv.arr[0], com->argv.arr, envvar);
		i = -1;
		while (++i < pcount)
			waitpid(pid[i], 0, 0);
		pcount = 0;
	}
	return (exit_status / 256);
}
