/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/25 19:03:27 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

char	**ft_add_file(char **tab, char *file)
{
	char	**new_tab;

	int i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = file;
	i++;
	new_tab[i] = NULL;
	free(tab);
	return (new_tab);
}

void	run_pipe(char *arg1, char **cmd_args1, char *cmd2_arg1, char **cmd2_args)
{
	char	*execve_cmd2_args[4];
	int		tube[2];
	pid_t	child2;

	printf("jusque la ca marche\n");
	execve_cmd2_args[0] = "/bin/cat";
	execve_cmd2_args[1] = "-e";
	execve_cmd2_args[2] = "fichier2.txt";
	execve_cmd2_args[3] = NULL;

	pipe(tube);
	tube[0] = open("fichier1.txt", O_WRONLY | O_APPEND);
	tube[1] = open("fichier2.txt", O_WRONLY | O_APPEND);

	child2 = fork();
	printf("fork 2: %d, PID : %i\n", child2, getpid());

	if (child2 == -1)
	{
		close(tube[0]);
		close(tube[1]);
		perror("Error");
	}
	if (child2 == 0)
	{
		dup2(tube[1], STDOUT_FILENO);
		close(tube[0]);
		execve(arg1, cmd_args1, NULL);
		perror("Error 2");
	}
	
	printf("dans le processus pere pipe: fork : %d, PID : %i\n", child2, getpid());
	dup2(tube[0], STDIN_FILENO);
	close(tube[1]);
	printf("debut du process fils pipe\n");
	wait(NULL);
	printf("fin du process fils pipe\n");
	execve(cmd2_arg1, cmd2_args, NULL);
	return;
}

int	main(int argc, char **argv)
{
	pid_t	child;
	char	*execve_arg1;
	char	**execve_cmd_args;
	char	**execve_cmd_args_extend;

	char	*execve_cmd2_arg1;
	char	**execve_cmd2_args;
	char	**execve_cmd2_args_extend;

	//ft_check_arg_error(argc, argv);
	execve_cmd_args = ft_split(argv[2], ' ');
	execve_cmd_args_extend = ft_add_file(execve_cmd_args, argv[1]);
	execve_arg1 = ft_strjoin("/bin/", execve_cmd_args_extend[0]);

	execve_cmd2_args = ft_split(argv[3], ' ');
	execve_cmd2_args_extend = ft_add_file(execve_cmd2_args, argv[4]);
	execve_cmd2_arg1 = ft_strjoin("/bin/", execve_cmd2_args_extend[0]);

	child = fork();
	printf("fork 1: %d, PID : %i\n", child, getpid());

	if (child == -1)
	{
		perror("Error");
	}
	if (child == 0)
	{
		printf("run pipe =>\n");
		run_pipe(execve_arg1, execve_cmd_args_extend, execve_cmd2_arg1, execve_cmd2_args_extend);
		perror("Error 2");
	}
	printf("dans le process pere : fork : %d, PID : %i\n", child, getpid());
	printf("debut du process fils main\n");
	wait(NULL);
	printf("fin du process fils main\n");

	free(execve_cmd_args_extend);
	free(execve_arg1);

	return (0);
}
