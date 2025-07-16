/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:40:35 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 17:09:44 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	parser(t_map *map)
{
	if (access(map->name, F_OK | R_OK) == -1)
	{
		free(map);
		ft_putstr_fd("Error\nCould not access or read map file! \n", 2);
		exit(1);
	}
	if (parse_name(map->name))
	{
		free(map);
		ft_putstr_fd("Error\nMap name is unsupported! \n", 2);
		exit(1);
	}
	if (parse_map(map))
	{
		free_tab_str(map->map);
		free(map);
		exit(1);
	}
}

int	parse_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		return (1);
	if (ft_strncmp(name + len - 4, ".ber", 5))
		return (1);
	if (name[len - 5] == '/')
		return (1);
	return (0);
}

int	parse_map(t_map *map)
{
	int	fd;

	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map file! \n", 2), 1);
	if (check_size(map, fd))
	{
		free_gnl_buffer(fd);
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCould not open map! \n", 2), 1);
	if (duplicate_map(map, fd))
	{
		free_gnl_buffer(fd);
		close(fd);
		return (ft_putstr_fd("Error\nCould not dup map! \n", 2), 1);
	}
	if (check_map_characteristics(map))
		return (1);
	return (0);
}

int	check_size(t_map *map, int fd)
{
	char	*line;

	line = skip_nl(fd);
	if (!line)
		return (ft_putstr_fd("Error\nEmpty map! \n", 2), 1);
	map->h_size = ft_strlen(line) - 1;
	map->v_size = 1;
	free(line);
	line = get_next_line(fd);
	while (line && line[0] != '\n')
	{
		map->v_size++;
		if (map->h_size != (int)ft_strlen(line) - end_nl(line))
		{
			free(line);
			return (ft_putstr_fd("Error\nMap is not rectangular! \n", 2), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (map->v_size < 3 || map->h_size < 3)
		return (ft_putstr_fd("Error\nNot enough rows or columns! \n", 2), 1);
	return (check_bottom(fd));
}

int	duplicate_map(t_map *map, int fd)
{
	int		i;
	char	*line;

	i = 0;
	map->map = ft_calloc(map->v_size + 1, sizeof(char *));
	if (!map->map)
		return (1);
	line = skip_nl(fd);
	while (i < map->v_size)
	{
		map->map[i] = ft_strdup(line);
		if (!map->map[i])
			return (1);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	map->map[i] = NULL;
	free(line);
	free_gnl_buffer(fd);
	close(fd);
	return (0);
}
