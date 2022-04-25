/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/25 13:49:54 by jrasser          ###   ########.fr       */
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
	return (new_tab);
}

int	main(int argc, char **argv)
{
	char	*execve_arg1;
	char	**execve_cmd_args;

	execve_cmd_args = ft_split(argv[2], ' ');
	execve_cmd_args = ft_add_file(execve_cmd_args, argv[1]);

	execve_arg1 = ft_strjoin("/bin/", execve_cmd_args[0]);


	

	//printf("arg1 : '%s'\n", execve_arg1);
	//printf("cmd_args : '%s'\n", execve_cmd_args[0]);

	//ft_check_arg_error(argc, argv);
	execve(execve_arg1, execve_cmd_args, NULL);

	return (0);
}
