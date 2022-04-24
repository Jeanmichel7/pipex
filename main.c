/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:09:07 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/24 20:40:23 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	main(int argc, char **argv)
{
	char	env[10] = "/bin/bash";
	char	*test[10];

	test[10] = NULL;
	//ft_check_arg_error(argc, argv);

	execve(env, argv, test);

	return (0);
}
