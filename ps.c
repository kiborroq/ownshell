#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "./incs/minishell.h"

extern char ** environ;

int main (int argc, char **argv, char **envv)
{
    // char buf[100];
    // char **strs;

    // read(0, buf, 99);
    // buf[99] = 0;

    // strs = ft_split(buf, ' ');
    // int i = 0;
    // while (strs[i])
    // {
    //     printf("|%s|\n", strs[i]);
    //     free(strs[i]);
    //     i++;
    // }
    // free(strs);
    // char * echo_args[] = { "echo", "asld", "asdasd", "123556", NULL };

    // if (!fork ()) {
    //         execve ("/bin/echo", echo_args, environ);
    //         fprintf (stderr, "an error occured\n");
    //         exit(1);
	// 		return (0);
    // }
	// int res;
	// wait(&res);
	// printf("%d\n", res);
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    // printf ("parent\n");
    
    printf("%s\n", envv[0]);
    return 0;
}
