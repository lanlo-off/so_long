/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:12:25 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 17:36:34 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_map(t_data *data, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->v_size)
	{
		j = 0;
		while (j < map->h_size)
		{
			if (map->map[i][j] == '1')
				print_img(data, data->img_wall, i, j);
			else
				print_img(data, data->img_floor, i, j);
			if (map->map[i][j] == 'P')
				print_img(data, data->img_player, i, j);
			else if (map->map[i][j] == 'C')
				print_img(data, data->img_collectible, i, j);
			else if (map->map[i][j] == 'E')
				print_img(data, data->img_exit, i, j);
			j++;
		}
		i++;
	}
}

void	print_img(t_data *data, void *img, int i, int j)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img,
		data->tile_size * j, data->tile_size * i);//a adapter, les 2 derniers args sont l'offset
}

int	init_images(t_data *data)
{
	int	w;
	int	h;

	data->img_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"sprites/1_wall.xpm", &w, &h);
	data->img_floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"sprites/0_floor.xpm", &w, &h);
	data->img_player = mlx_xpm_file_to_image(data->mlx_ptr,
			"sprites/P_player.xpm", &w, &h);
	data->img_collectible = mlx_xpm_file_to_image(data->mlx_ptr,
			"sprites/C_item.xpm", &w, &h);
	data->img_exit = mlx_xpm_file_to_image(data->mlx_ptr,
			"sprites/E_exit.xpm", &w, &h);
	if (!data->img_wall || !data->img_floor || !data->img_player
		|| !data->img_collectible || !data->img_exit)
	{
		ft_putstr_fd("Could not load one of the sprites\n", 2);
		return (0);
	}
	return (1);
}
