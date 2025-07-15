/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:20:06 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 10:15:49 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_characteristics(t_map *map)
{
	if (check_outlines(map))
		return (ft_putstr_fd("Error\nMap has wrong outlines !", 2), 1);
	if (count_spe_tiles(map))
		return (1);
	if (valid_path(map))
		return (ft_putstr_fd("Error\nMap has no valid path to finish !", 2), 1);
	return (0);
}

int	check_outlines(t_map *map)
{
	int	i;
	
	i = 0;
	while ((map->map[0][i] && map->map[0][i] == '1'))//first line
		i++;
	if (i != map->h_size)
		return (1);
	i = 0;
	while (map->map[map->v_size - 1][i] && map->map[map->v_size - 1][i] == 1)//last line
		i++;
	if (i != map->h_size)
		return (1);
	i = 0;
	while ((map->map[i][0] && map->map[i][0] == '1'))//first column
		i++;
	if (i != map->h_size)
		return (1);
	i = 0;
	while (map->map[i][map->h_size - 1] && map->map[i][map->h_size - 1] == 1)//last column
		i++;
	if (i != map->h_size)
		return (1);
	return (0);
}

int	count_spe_tiles(t_map *map)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	exit = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (invalid_char(map, map->map[i][j], i, j))
				return (ft_putstr_fd("Error\nInvalid character in map!", 2), 1);
			j++;
		}
		i++;
	}
	if (map->exit != 1)
		return (ft_putstr_fd("Error\nWrong exit !", 2), 1);
	if (!map->player != 1)
		return (ft_putstr_fd("Error\nWrong starting position !", 2), 1);
	if (map->collec < 1)
		return (ft_putstr_fd("Error\nNot enough collectibles !", 2), 1);
	return (0);
}

int	invalid_char(t_map *map, char c, int i, int j)
{
	if (c == '0' || c == '1')
		return (0);
	if (c == 'E')
	{
		map->exit_i = i;
		map->exit_j = j;
		map->exit++;
		return (0);
	}
	if (c == 'C')
	{
		map->collec++;
		return (0);
	}
	if (c == 'P')
	{
		map->start_i = i;
		map->start_j = j;
		map->player++;
		return (0);
	}
	return (1);
}

int	valid_path(t_map *map)
{
	flood_fill(map, map->start_i, map->start_j);
	if (!found_way(map->map))
		return (1);
	reverse_flood(map, map->start_i, map->start_j);
	return (0);
}
