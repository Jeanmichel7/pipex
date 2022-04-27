/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/27 17:23:03 by jrasser          ###   ########.fr       */
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

/*
void	run_pipe(char *arg1, char **cmd_args1, char *cmd2_arg1, char **cmd2_args)
{
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
		//dup2(tube[1], STDOUT_FILENO);
		//close(tube[0]);
		execve(arg1, cmd_args1, NULL);
		perror("Error 2");
	}
	
	printf("dans le processus pere pipe: fork : %d, PID : %i\n", child2, getpid());
	//dup2(tube[0], STDIN_FILENO);
	//close(tube[1]);
	printf("debut du process fils pipe\n");
	wait(NULL);
	printf("fin du process fils pipe\n");
	execve(cmd2_arg1, cmd2_args, NULL);
	return;
}
*/

int	main(int argc, char **argv, char **env)
{
	pid_t	child;
	int		tube[2];
	int 	fd1;
	int		fd2;
	char	*cmd1_fct;
	char	**cmd1_args;
	char	*cmd2_fct;
	char	**cmd2_args;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);	
	cmd1_args = ft_split(argv[2], ' ');
	cmd1_fct = ft_strjoin("/bin/", cmd1_args[0]);
	cmd2_args = ft_split(argv[3], ' ');
	cmd2_fct = ft_strjoin("/bin/", cmd2_args[0]);
	pipe(tube);
	child = fork();
	if (child == -1)
	{
		perror("Error");
	}
	if (child == 0)
	{
		dup2(fd1, STDIN_FILENO);
		dup2(tube[1], STDOUT_FILENO);
		close(tube[0]);
		execve(cmd1_fct, cmd1_args, env);
		close(fd1);
	}

	waitpid(child, NULL, WNOHANG);
	dup2(tube[0], STDIN_FILENO);
	close(tube[1]);
	dup2(fd2, STDOUT_FILENO);
	execve(cmd2_fct, cmd2_args, env);
	close(fd2);

	return (0);
}
