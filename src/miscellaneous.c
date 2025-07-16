/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:02:46 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 12:43:53 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	end_nl(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (!len)
		return (0);
	return (line[len - 1] == '\n');
}

char	*skip_nl(int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	free_gnl_buffer(int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}