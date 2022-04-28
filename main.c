/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/28 14:17:28 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_errputstr(char *str)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
	}
}

char	*ft_checkacces(char **env, char *cmd)
{
	int		i;
	int		state;
	char	*path_cmd_test;
	char	*paths;
	char	**path_tab;

	i = -1;
	state = 1;
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
	int		fd1;
	int		fd2;
	char	*cmd1_fct;
	char	**cmd1_args;
	char	*cmd2_fct;
	char	**cmd2_args;

	ft_check_arg_error(argc, argv);
	cmd1_args = ft_split(argv[2], ' ');
	cmd1_fct = ft_checkacces(env, cmd1_args[0]);
	cmd2_args = ft_split(argv[3], ' ');
	cmd2_fct = ft_checkacces(env, cmd2_args[0]);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (cmd1_fct == NULL)
	{
		ft_errputstr("zsh: command not found: ");
		ft_errputstr(cmd1_args[0]);
		ft_errputstr("\n");
	}
	if (cmd2_fct == NULL)
	{
		ft_errputstr("zsh: command not found: ");
		ft_errputstr(cmd2_args[0]);
		ft_errputstr("\n");
		return (0);
	}
	if (fd1 == - 1)
	{
		ft_errputstr("zsh: no such file or directory: ");
		ft_errputstr(argv[1]);
		ft_errputstr("\n");
		return (0);
	}
	if (fd2 == - 1)
	{
		perror("opening or creation impossible\n");
		ft_errputstr(strerror(errno));
		return (0);
	}
	pipe(tube);
	child = fork();
	if (child == -1)
	{
		perror("Error");
		return (1);
	}
	if (child == 0)
	{
		dup2(fd1, STDIN_FILENO);
		dup2(tube[1], STDOUT_FILENO);
		close(tube[0]);
		if (execve(cmd1_fct, cmd1_args, env) == -1 )
		{
			if (cmd1_fct != NULL)
				ft_errputstr(strerror(errno));
			return (1);
		}
		close(fd1);
	}
	else
	{
		waitpid(child, NULL, WNOHANG);
		dup2(tube[0], STDIN_FILENO);
		close(tube[1]);
		dup2(fd2, STDOUT_FILENO);
		if (execve(cmd2_fct, cmd2_args, env) == -1)
		{
			ft_errputstr(strerror(errno));
			return (1);
		}
		close(fd2);
	}
	free(cmd1_fct);
	free(cmd1_args);
	free(cmd2_fct);
	free(cmd1_args);

	return (0);
}
