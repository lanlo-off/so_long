/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:20:06 by llechert          #+#    #+#             */
/*   Updated: 2025/07/10 17:48:56 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_characteristics(t_game *game)
{
	if (check_outlines(game, game->map))
		return (ft_putstr_fd("Error\nMap has wrong outlines !", 2), 1);
	if (count_spe_tiles(game))
		return (1);
	if (valid_path(game))
		return (ft_putstr_fd("Error\nMap has no valid path to finish !", 2), 1);
	return (0);
}

int	check_outlines(t_game *game, char **map)
{
	int	i;
	
	i = 0;
	while ((map[0][i] && map[0][i] == '1'))//first line
		i++;
	if (i != game->h_size)
		return (1);
	i = 0;
	while (map[game->v_size - 1][i] && map[game->v_size - 1][i] == 1)//last line
		i++;
	if (i != game->h_size)
		return (1);
	i = 0;
	while ((map[i][0] && map[i][0] == '1'))//first column
		i++;
	if (i != game->h_size)
		return (1);
	i = 0;
	while (map[i][game->h_size - 1] && map[i][game->h_size - 1] == 1)//last column
		i++;
	if (i != game->h_size)
		return (1);
	return (0);
}

int	count_spe_tiles(t_game *game)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	exit = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (invalid_char(game, game->map[i][j], i, j))
				return (ft_putstr_fd("Error\nInvalid character in map!", 2), 1);
			j++;
		}
		i++;
	}
	if (game->exit != 1)
		return (ft_putstr_fd("Error\nWrong exit !", 2), 1);
	if (!game->player != 1)
		return (ft_putstr_fd("Error\nWrong starting position !", 2), 1);
	if (game->collec < 1)
		return (ft_putstr_fd("Error\nNot enough collectibles !", 2), 1);
	return (0);
}

int	invalid_char(t_game *game, char c, int i, int j)
{
	if (c == '0' || c == '1')
		return (0);
	if (c == 'E')
	{
		game->exit_i = i;
		game->exit_j = j;
		game->exit++;
		return (0);
	}
	if (c == 'C')
	{
		game->collec++;
		return (0);
	}
	if (c == 'P')
	{
		game->start_i = i;
		game->start_j = j;
		game->player++;
		return (0);
	}
	return (1);
}

int	valid_path(t_game *game)
{
	flood_fill(game, game->start_i, game->start_j);
	if (!found_way(game->map))
		return (1);
	reverse_flood(game, game->start_i, game->start_j);
	return (0);
}
