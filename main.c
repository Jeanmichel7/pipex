/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/25 16:02:35 by jrasser          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	char	*execve_arg1;
	char	**execve_cmd_args;
	char	**execve_cmd_args_extend;
	pid_t	father;

	execve_cmd_args = ft_split(argv[2], ' ');
	execve_cmd_args_extend = ft_add_file(execve_cmd_args, argv[1]);
	execve_arg1 = ft_strjoin("/bin/", execve_cmd_args_extend[0]);
	father = fork();
	printf("fork : %d, PID : %i\n", father, getpid());
	
	if (father > 0)
	{
		//execve(execve_arg1, execve_cmd_args_extend, NULL);
		printf("dans le process pere : fork : %d, PID : %i\n", father, getpid());
		
		printf("debut du process fils\n");
		wait(NULL);
		printf("fin du process fils \n");
	}
	if (father == 0)
	{
		printf("dans le processus fils : fork : %d, PID : %i\n", father, getpid());
		execve(execve_arg1, execve_cmd_args_extend, NULL);
	}

	printf("arg1 : '%s'\n", execve_arg1);
	printf("cmd_args : '%s'\n", execve_cmd_args_extend[0]);

	free(execve_cmd_args_extend);
	free(execve_arg1);

	//ft_check_arg_error(argc, argv);

	return (0);
}
