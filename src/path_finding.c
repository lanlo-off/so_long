/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:46:51 by llechert          #+#    #+#             */
/*   Updated: 2025/07/10 17:04:29 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	flood_fill(t_game *game, int i, int j)
{
	if (i < 0 || i >= game->v_size || j < 0 || j > game->h_size)
		return ;
	if (!process_target(game->map[i][j]))
		return ;
	flood_fill(game, i - 1, j);
	flood_fill(game, i + 1, j);
	flood_fill(game, i, j - 1);
	flood_fill(game, i, j + 1);
}

int	process_target(char c)
{
	if (c == '0' || c == "C" || c == 'E' || c == 'P')//0 devient F et les autres deviennent leur minuscule
	{
		c += 32;
		return (1);
	}
	return (0);
}

void	reverse_flood(t_game *game, int i, int j)
{
	if (i < 0 || i >= game->v_size || j < 0 || j > game->h_size)
		return ;
	if (!rev_process_target(game->map[i][j]))
		return ;
	reverse_flood(game, i - 1, j);
	reverse_flood(game, i + 1, j);
	reverse_flood(game, i, j - 1);
	reverse_flood(game, i, j + 1);
}

int	rev_process_target(char c)
{
	if (c == 'F' || c == "c" || c == 'e' || c == 'p')//F devient 0 et les autres deviennent leur majuscule
	{
		c -= 32;
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