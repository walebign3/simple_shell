#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

/**
 * main - super simple shell
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	pid_t ch;
	char *tok, *lnptr = NULL;
	size_t i, n;
	char **cmd = malloc(64 * sizeof(char*));

	if (!cmd)
	{
		perror("lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	if (argc != 1)
		perror("./shell: No such file or directory");
	while(1)
	{
		write(STDOUT_FILENO,"#cisfun$ ",10);
		if (getline(&lnptr, &n, stdin) == -1)
		{
			exit(EXIT_FAILURE);
			break;
		}
		tok = strtok(lnptr, "\n\r");
		for (i = 0; i < 1 && tok != NULL; i++)
		{
			cmd[i] = tok;
		}
		cmd[i] = NULL;
		ch = fork();
		if (ch == 0)
		{
			if (execve(cmd[0], cmd, NULL))
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		if (ch > 0)
		wait(NULL);
	}
	write(STDOUT_FILENO,"\n",1);
	free(cmd);
	free(lnptr);
	return 0;
}
