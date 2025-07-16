/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:46:51 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 16:31:46 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	flood_fill(t_map *map, int i, int j)
{
	if (i < 0 || i >= map->v_size || j < 0 || j >= map->h_size)
		return ;
	if (!process_target(&map->map[i][j]))
		return ;
	flood_fill(map, i - 1, j);
	flood_fill(map, i + 1, j);
	flood_fill(map, i, j - 1);
	flood_fill(map, i, j + 1);
}

int	process_target(char *c)
{
	if (*c == 'C' || *c == 'E' || *c == 'P')
	{
		*c += 32;
		return (1);
	}
	else if (*c == '0')
	{
		*c = 'a';
		return (1);
	}
	return (0);
}

void	reverse_flood(t_map *map, int i, int j)
{
	if (i < 0 || i >= map->v_size || j < 0 || j > map->h_size)
		return ;
	if (!rev_process_target(&map->map[i][j]))
		return ;
	reverse_flood(map, i - 1, j);
	reverse_flood(map, i + 1, j);
	reverse_flood(map, i, j - 1);
	reverse_flood(map, i, j + 1);
}

int	rev_process_target(char *c)
{
	if (*c == 'c' || *c == 'e' || *c == 'p')
	{
		*c -= 32;
		return (1);
	}
	else if (*c == 'a')
	{
		*c = '0';
		return (1);
	}
	return (0);
}

int	found_way(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
