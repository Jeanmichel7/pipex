/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/25 17:59:28 by jrasser          ###   ########.fr       */
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

void	run_pipe()
{

	char	*execve_arg1;
	char	*execve_cmd_args[3];
	char	**execve_cmd_args_extend;
	int		tube[2];
	pid_t	child2;
	char	*execve_cmd2_args[3];

	
	printf("jusque la ca marche\n");


	execve_cmd_args[0] = "/bin/grep";
	execve_cmd_args[1] = "key";
	execve_cmd_args[2] = NULL;
	printf("jusque la ca marche\n");

	execve_cmd2_args[0] = "/bin/cat";
	execve_cmd2_args[1] = "-e";
	execve_cmd2_args[2] = NULL;
/*
	execve_cmd_args = ft_split(argv[2], ' ');
	execve_cmd_args_extend = ft_add_file(execve_cmd_args, argv[1]);
	execve_arg1 = ft_strjoin("/bin/", execve_cmd_args_extend[0]);
*/

	child2 = fork();
	printf("fork 2: %d, PID : %i\n", child2, getpid());

	pipe(tube);
	
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
		printf("dans le processus fils : fork : %d, PID : %i\n", child2, getpid());
		execve("/bin/grep", execve_cmd_args, NULL);
		perror("Error 2");
	}
	
	printf("dans le processus pere : fork : %d, PID : %i\n", child2, getpid());
	dup2(tube[0], STDIN_FILENO);
	close(tube[1]);
	printf("debut du process fils pipe\n");
	wait(NULL);
	printf("fin du process fils pipe\n");
	execve("/bin/cat", execve_cmd2_args, NULL);
	return;

	


	//printf("arg1 : '%s'\n", execve_arg1);
	//printf("cmd_args : '%s'\n", execve_cmd_args_extend[0]);




	//free(execve_cmd_args_extend);
	//free(execve_arg1);
}

int	main(int argc, char **argv)
{
	pid_t	child;

	child = fork();
	printf("fork 1: %d, PID : %i\n", child, getpid());

	if (child == -1)
	{
		perror("Error");
	}
	if (child == 0)
	{
		printf("run pipe =>\n");
		run_pipe();
		perror("Error 2");
	}
	printf("dans le process pere : fork : %d, PID : %i\n", child, getpid());
	printf("debut du process fils main\n");
	wait(NULL);
	printf("fin du process fils main\n");

	

	//ft_check_arg_error(argc, argv);

	return (0);
}


/*
int	main(int argc, char **argv)
{
	char	*execve_arg1;
	char	**execve_cmd_args;
	char	**execve_cmd_args_extend;
	pid_t	child;
	int		tube[2];



	char	**execve_cmd2_args;
	execve_cmd2_args[0] = "/bin/cat";
	execve_cmd2_args[1] = "-e";
	execve_cmd2_args[2] = NULL;


	execve_cmd_args = ft_split(argv[2], ' ');
	execve_cmd_args_extend = ft_add_file(execve_cmd_args, argv[1]);
	execve_arg1 = ft_strjoin("/bin/", execve_cmd_args_extend[0]);
	child = fork();
	printf("fork : %d, PID : %i\n", child, getpid());



	pipe(tube);
	
	if (child == -1)
	{
		close(tube[0]);
		close(tube[1]);
		perror("Error");
	}
	if (child == 0)
	{
		dup2(tube[1], STDOUT_FILENO);
		close(tube[0]);
		printf("dans le processus fils : fork : %d, PID : %i\n", child, getpid());
		execve(execve_arg1, execve_cmd_args_extend, NULL);
		perror("Error 2");
	}
	else // dans le pere
	{
		dup2(tube[0], STDIN_FILENO);
		close(tube[1]);
		wait(NULL);
		execve("/bin/cat", execve_cmd2_args, NULL);

	}
	printf("arg1 : '%s'\n", execve_arg1);
	printf("cmd_args : '%s'\n", execve_cmd_args_extend[0]);



	printf("dans le process pere : fork : %d, PID : %i\n", child, getpid());
		
	printf("debut du process fils\n");
	wait(NULL);
	printf("fin du process fils \n");


	free(execve_cmd_args_extend);
	free(execve_arg1);

	//ft_check_arg_error(argc, argv);

	return (0);
}

*/