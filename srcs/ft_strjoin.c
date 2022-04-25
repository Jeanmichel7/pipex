/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:26:09 by jrasser           #+#    #+#             */
/*   Updated: 2022/04/25 13:38:51 by jrasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin(char *line, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer)) + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		new_str[i] = line[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j])
		new_str[i++] = buffer[j++];

	new_str[i] = '\0';
	return (new_str);
}