/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/27 19:52:09 by jrasser          ###   ########.fr       */
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

char	*ft_checkacces (char **env, char *cmd) {
	int 	i = -1;
	int		state = 1;
	char	*path_cmd_test;
	char	*paths;
	char	**path_tab;

	while (env[++i])
		if (strncmp(env[i], "PATH", 4) == 0)
			paths = env[i];
	paths = paths + 5;
	path_tab = ft_split(paths, ':');
	i = 0;
	while (path_tab[i] && state)
	{
		path_cmd_test = ft_strjoin(ft_strjoin(path_tab[i], "/"), cmd);
		if (access(path_cmd_test, F_OK | X_OK) == 0)
			return (path_cmd_test);
		i++;
	}
	return (NULL);
}

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
	int		ret;


	char	*cmd1_path;
	char	*cmd2_path;

	cmd1_args = ft_split(argv[2], ' ');
	cmd1_path = ft_checkacces(env, cmd1_args[0]);
	cmd1_fct = cmd1_path;
	printf("cmd 1 : %s\n", cmd1_fct);

	cmd2_args = ft_split(argv[3], ' ');
	cmd2_path = ft_checkacces(env, cmd2_args[0]);
	cmd2_fct = cmd2_path;
	printf("cmd 2 : %s\n", cmd2_fct);



	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);


	pipe(tube);
	//tube[0] = STDIN_FILENO;
	//tube[1] = STDOUT_FILENO;
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
		ret = execve(cmd1_fct, cmd1_args, env);
		if (ret == -1)
			perror("Error cmd 1");
		close(fd1);
	}

	waitpid(child, NULL, WNOHANG);
	dup2(tube[0], STDIN_FILENO);
	close(tube[1]);
	dup2(fd2, STDOUT_FILENO);
	ret = execve(cmd2_fct, cmd2_args, env);
	if (ret == -1)
		perror("Error cmd 2");
	close(fd2);

	return (0);
}
