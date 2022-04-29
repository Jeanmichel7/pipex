/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:56:23 by jeulliot          #+#    #+#             */
/*   Updated: 2022/04/29 18:26:25 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_errputstr(char *str, int stop, int code)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		if (stop)
			exit(code);
	}
}

void	ft_check_arg_error(int argc, char **argv)
{
	(void)argv;
	if (argc != 5)
	{
		write (2, "Error\n", 6);
		exit (1);
	}
}

char	*ft_checkacces(char **env, char *cmd)
{
	int		i;
	int		state;
	char	*path_cmd_test;
	char	*paths;
	char	**path_tab;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
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

void	ft_check_cmds(char *fct1, char *args1, char *fct2, char *args2)
{
	if (fct1 == NULL)
	{
		ft_errputstr("zsh: command not found: ", 0, 0);
		ft_errputstr(args1, 0, 0);
		ft_errputstr("\n", 0, 0);
	}
	if (fct2 == NULL)
	{
		ft_errputstr("zsh: command not found: ", 0, 0);
		ft_errputstr(args2, 0, 0);
		ft_errputstr("\n", 1, 127);
	}
}

void	ft_check_fds(int fd1, int fd2, char *fct)
{
	if (fd1 == -1)
	{
		ft_errputstr("zsh: no such file or directory: ", 0, 0);
		ft_errputstr(fct, 0, 0);
		ft_errputstr("\n", 0, 0);
	}
	if (fd2 == -1)
	{
		ft_errputstr(strerror(errno), 1, 1);
	}
}
