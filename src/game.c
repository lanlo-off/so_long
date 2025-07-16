/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:21:28 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 17:11:01 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	start_game(t_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width,
			data->height, data->map->name);
	if (!data->win_ptr)
		exit_window(data, 1);
	if (!init_images(data))
		exit_game(data, 1);
	render_map(data, data->map);
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0, exit_game, data);
	mlx_loop(data->mlx_ptr);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit_game(data, 0);
	else if (keycode == 'w' || keycode == 119 || keycode == 65362)
		move_player(data, -1, 0);
	else if (keycode == 's' || keycode == 115 || keycode == 65364)
		move_player(data, 1, 0);
	else if (keycode == 'a' || keycode == 97 || keycode == 65361)
		move_player(data, 0, -1);
	else if (keycode == 'd' || keycode == 100 || keycode == 65363)
		move_player(data, 0, 1);
	return (0);
}

void	move_player(t_data *data, int di, int dj)
{
	int		new_i;
	int		new_j;
	char	tile;

	new_i = data->player_i + di;
	new_j = data->player_j + dj;
	tile = data->map->map[new_i][new_j];
	if (tile == '1')
		return ;
	if (tile == 'C')
		data->collected++;
	if (new_i == data->map->exit_i && new_j == data->map->exit_j
		&& data->collected == data->map->collec)
	{
		print_move(++data->moves);
		exit_game(data, 0);
	}
	data->map->map[data->player_i][data->player_j] = '0';
	data->map->map[new_i][new_j] = 'P';
	data->player_i = new_i;
	data->player_j = new_j;
	print_move(++data->moves);
	render_map(data, data->map);
}

void	print_move(int moves)
{
	ft_printf("Moves: %d\n", moves);
}
