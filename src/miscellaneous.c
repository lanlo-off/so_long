/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:02:46 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 17:03:21 by llechert         ###   ########.fr       */
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

int	check_bottom(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line && line[0])
	{
		free(line);
		return (ft_putstr_fd("Error\nThere are things below your map! \n", 2), 1);
	}
	return (0);
}
