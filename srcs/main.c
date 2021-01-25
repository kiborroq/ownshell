/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:57:40 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/26 02:01:33 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char    *get_env(char **envvar, char *target_key, int mode)
{
    char    *current_key;
    char    *delimiter;
    int     i;
    int     env_not_found;    

	env_not_found = 1;
    i = 0;
    while (env_not_found && envvar[i])
    {
        delimiter = ft_strchr(envvar[i], '=');
        current_key = ft_substr(envvar[i], 0, delimiter - envvar[i]);
        if (!ft_strcmp(current_key, target_key))
            env_not_found = 0;
        free(current_key);
        i++;
    }
    if (env_not_found)
        return (NULL);
    return (mode == 1 ? delimiter + 1 : ft_itoa(i - 1));
}

void	print_strs(char **strs)
{
	while (*strs)
	{
		printf("|%s|\n", *strs);
		strs++;
	}
}

int main(int argc, char **argv, char **envvar)
{
	t_comand *com;
	char	*line = "		echo  $USER	 '123''123'\"123\" \"$PATH ; | ' ' > >> < \\' \" > kk >> gg | cat < \"k\"'p't >> $KK; ";
	// char	*line = " \" k\\\\k \" ";
	(void)argc;
	(void)argv;
	while (*line != '\n' && *line)
	{
		com = get_next_comand(&line, envvar);
		printf("argv:\n");
		print_strs(com->argv.arr);

		printf("redir_in:\n");
		print_strs(com->redir_in.arr);

		printf("redir_out:\n");
		print_strs(com->redir_out.arr);

		printf(">> ?: ");
		printf("%d\n", com->add_out);

		printf("pipe_after: ");
		printf("%d\n", com->pipe_after);

		printf("message: ");
		if (com->message)
		{
			printf("%s\n", com->message);
			free_comand(com);
			return (0);
		}
		else
			printf("OK\n");
		printf("\n");
		free_comand(com);
	}
	return 0;
}
