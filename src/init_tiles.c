/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:08:10 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 11:15:40 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_images(t_data data)
{
	int w;
	int h;

	data.img->wall = mlx_xpm_file_to_image(data.mlx_ptr, "sprites/1_wall.xpm", &w, &h);
	data.img->floor = mlx_xpm_file_to_image(data.mlx_ptr, "sprites/0_floor.xpm", &w, &h);
	data.img->player = mlx_xpm_file_to_image(data.mlx_ptr, "sprites/P_player.xpm", &w, &h);
	data.img->collectible = mlx_xpm_file_to_image(data.mlx_ptr, "sprites/C_collectible.xpm", &w, &h);
	data.img->exit = mlx_xpm_file_to_image(data.mlx_ptr, "sprites/E_exit.xpm", &w, &h);
}