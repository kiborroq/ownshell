/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/28 10:40:56 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incs/minishell.h"

void	print_strs(char **strs)
{
	while (*strs)
	{
		printf("|%s|\n", *strs);
		strs++;
	}
}

int		set_fds_and_run(t_comand *com, char ***envvar, t_fds *fds)
{
	int	status_in;
	int	status_out1;
	int	status_out2;

	status_in = 0;
	status_out1 = 0;
	status_out2 = 0;
	fds->save_fd_in = dup(STDIN_FILENO);
	fds->save_fd_uot = dup(STDOUT_FILENO);
	if (com->pipe_before == 1 && com->fd_in == 0)
	{
		dup2(fds->before_fd[0], STDIN_FILENO);
		status_in = 1;
	}
	else if (com->fd_in > 0)
	{
		if (com->pipe_before == 1)
			close(fds->before_fd[0]);
		dup2(com->fd_in, STDIN_FILENO);
		status_in = 2;
	}
	if (com->pipe_after == 1)
	{
		pipe(fds->after_fd);
		dup2(fds->after_fd[1], STDOUT_FILENO);
		status_out1 = 3;
		if (com->fd_out > 0)
		{
			close(fds->after_fd[1]);
			status_out1 = 0;
		}
	}
	if (com->fd_out > 0)
	{
		dup2(com->fd_out, STDOUT_FILENO);
		status_out2 = 4;
	}
	run_command(com->argv.arr[0], com->argv.arr, envvar);
	if (status_in == 1)
		close(fds->before_fd[0]);
	else if (status_in == 2)
		close(com->fd_in);
	if (status_out1 == 3)
		close(fds->after_fd[1]);
	else if (status_out2 == 4)
		close(com->fd_out);
	dup2(fds->save_fd_in, STDIN_FILENO);
	close(fds->save_fd_in);
	dup2(fds->save_fd_uot, STDOUT_FILENO);
	close(fds->save_fd_uot);
	fds->before_fd[0] = fds->after_fd[0];
	fds->before_fd[1] = fds->after_fd[1];
	return (KO);
}

void	init_fds(t_fds *fds)
{
	fds->after_fd[0] = 0;
	fds->after_fd[1] = 0;
	fds->before_fd[0] = 0;
	fds->before_fd[1] = 0;
	fds->fd_in = 0;
	fds->fd_uot = 0;
	fds->save_fd_in = 0;
	fds->save_fd_uot = 0;
	fds->status_in = 0;
	fds->status_out = 0;
}

int		do_allcomands(char *line, char ***envvar)
{
	t_comand	*com = 0;
	t_fds		fds;
	int	pipe_before;

	pipe_before = 0;
	init_fds(&fds);
	line = ft_skip_spaces(line);
	if (ft_strlen(line) == 0)
		return (OK);
	while (*line && *line != '\n')
	{
		com = get_next_comand(&line, *envvar);
		if (com == 0)
			return (KO);
		if (com->message == 0)
		{
			com->pipe_before = pipe_before;
			set_fds_and_run(com, envvar, &fds);
			pipe_before = com->pipe_after;
		}
		else
			printf("%s\n", com->message);
		// free_comand(com); ??????????
	}
	return (OK);
}

int main(int argc, char **argv, char **envp)
{
	// char	*line = "		echo  $? $ $USER $KK666	 '123''123'\"123\" \"$PATH ; | ' ' \\\" > >> < \\' \" > kk >> gg | cat < Makefile >> lps < gg < \"k\"'p't | echo 123 | echo 3943 ";
	(void)argc;
	(void)argv;
	char	*line;
	char	**envvar;

	envvar = read_envp(envp);
	while (1)
	{
		ft_printf("minishell:%s$ ", get_env(envvar, "PWD", 1));
		if (get_next_line(0, &line) < 0)
			break ;
		do_allcomands(line, &envvar);
		ft_freeptr((void **)&line);
	}
	ft_printf("\n");
	return (0);
}

// int		main(int argc, char **argv, char **envp)
// {
// 	char	**envvar = read_envp(envp);
// 	char	**av;
// 	char	*command = ft_strdup(argv[1]);
// 	int		j = 0;
// 	// int		i = 0;

// 	(void)envvar;
// 	av = (char **)malloc(argc * sizeof(char *));
// 	while (++j < argc)
// 		av[j - 1] = ft_strdup(argv[j]);
// 	run_command(command, av, &envvar);
// 	run_command(ft_strdup("pwd"), ft_split("pwd", ' '), &envvar);
// 	run_command(command, ft_split("cd ..", ' '), &envvar);
// 	run_command(ft_strdup("pwd"), ft_split("pwd", ' '), &envvar);
// 	///TESTS///////
// 	if(!ft_strcmp(argv[1], "export") && argc > 2)
// 		run_command(ft_strdup("env"), ft_split("env", ' '), &envvar);
// 	if(!ft_strcmp(argv[1], "cd"))
// 		run_command(ft_strdup("pwd"), ft_split("pwd", ' '), &envvar);
// 	if((!ft_strcmp(argv[1], "export") && argc > 2) ||
// 	!ft_strcmp(argv[1], "unset"))
// 	{
// 		while (envvar[i])
// 			ft_printf("%s\n", envvar[i++]);
// 	}
// 	return (0);
// }

// int		main(int argc, char **argv, char **envp)
// {
// 	t_comand	com;
// 	char		**envvar = read_envp(envp);

// 	(void)argc;
// 	(void)argv;
// 	com.argv.arr = (char **)malloc(3 * sizeof(char *));
// 	com.argv.arr[0] = ft_strdup("cat");
// 	com.argv.arr[1] = ft_strdup("tes");
// 	com.argv.arr[2] = 0;
// 	com.pipe_before = 0;
// 	com.pipe_after = 1;
// 	handle_pipe(&com, &envvar);
// 	com.argv.arr = (char **)malloc(3 * sizeof(char *));
// 	com.argv.arr[0] = ft_strdup("ech");
// 	com.argv.arr[1] = 0;
// 	com.argv.arr[2] = 0;
// 	com.pipe_before = 1;
// 	com.pipe_after = 0;
// 	handle_pipe(&com, &envvar);
// 	// com.argv.arr = (char **)malloc(3 * sizeof(char *));
// 	// com.argv.arr[0] = ft_strdup("grep");
// 	// com.argv.arr[1] = ft_strdup("hello ");
// 	// com.argv.arr[2] = 0;
// 	// com.pipe_before = 1;
// 	// com.pipe_after = 0;
// 	// handle_pipe(&com, &envvar);
// 	return (0);
// }



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