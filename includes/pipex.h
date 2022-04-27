/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:21:46 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/27 19:51:33 by jrasser          ###   ########.fr       */
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

void	ft_check_arg_error(int argc, char **argv);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *line, char *buffer);
size_t	ft_strlen(const char *str);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);


#endif