/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:38:02 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 16:54:59 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	exit_init(t_data *data, int exit_code)
{
	free_tab_str(data->map->map);
	free(data->map);
	exit(exit_code);
	return (0);
}

int	exit_window(t_data *data, int exit_code)
{
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit_init(data, exit_code);
	return (0);
}

int	exit_game(t_data *data, int exit_code)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img_wall);
	mlx_destroy_image(data->mlx_ptr, data->img_floor);
	mlx_destroy_image(data->mlx_ptr, data->img_player);
	mlx_destroy_image(data->mlx_ptr, data->img_collectible);
	mlx_destroy_image(data->mlx_ptr, data->img_exit);
	exit_window(data, exit_code);
	return (0);
}
