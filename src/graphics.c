/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:12:25 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 11:15:44 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_map(t_data data, t_map *map)
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
				put_image(data, data.img->wall, i, j);
			else
				put_image(data, data.img->floor, i, j);
			if (map->map[i][j] == 'P')
				put_image(data, data.img->player, i, j);
			else if (map->map[i][j] == 'C')
				put_image(data, data.img->collectible, i, j);
			else if (map->map[i][j] == 'E')
				put_image(data, data.img->exit, i, j);
			j++;
		}
		i++;
	}
}

void	print_img(t_data data, void *img, int i, int j)
{
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img,
		data.tile_size * i, data.tile_size * j);//a adapter
}