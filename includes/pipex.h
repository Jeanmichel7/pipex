/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:21:46 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/29 17:57:28 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_var
{
	pid_t	child;
	int		tube[2];
	int		fd1;
	int		fd2;
	char	*cmd1_fct;
	char	**cmd1_args;
	char	*cmd2_fct;
	char	**cmd2_args;
}	t_var;

void	ft_check_arg_error(int argc, char **argv);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *line, char *buffer);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);

/* CHECK */
char	*ft_checkacces(char **env, char *cmd);
void	ft_check_cmds(char *fct1, char *args1, char *fct2, char *args2);
void	ft_check_fds(int fd1, int fd2, char *fct);
void	ft_errputstr(char *str, int stop, int code);
void	ft_check_fds(int fd1, int fd2, char *fct);
#endif