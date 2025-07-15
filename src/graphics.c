/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:12:25 by llechert          #+#    #+#             */
/*   Updated: 2025/07/14 16:18:40 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_background(t_data data)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (data.game->map[y] != NULL)
	{
		while (data.game->map[y][i] != '\0')
		{
			if (data.game->map[y][i] == data->content.wall)
				print_img(data, data->img.img_wall, i, y);
			if (data.game->map[y][i] == data->content.space)
				print_img(data, data->img.img_floor, i, y);
			i++;
		}
		i = 0;
		y++;
	}
}

void	render_other(t_data data)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (data.game->map[y] != NULL)
	{
		while (data.game->map[y][i])
		{
			if (data.game->map[y][i] == data->content.collect)
				print_img(data, data->img.img_collect, i, y);
			if (data.game->map[y][i] == data->content.player)
			{
				data->pos.x = i * data->img.width;//a adapter
				data->pos.y = y * data->img.height;//a adapter
				print_img(data, data->img.img_player, i, y);
			}
			if (data.game->map[y][i] == data->content.exit)
				print_img(data, data->img.img_exit, i, y);
			i++;
		}
		i = 0;
		y++;
	}
}

int	render(t_data data)
{
	render_background(data);
	render_other(data);
	return (0);
}

void	core_render(t_data data)
{
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			(data->width * data->img.width), (data->height * data->img.height),//a adapter
			"So_long");
	if (data.win_ptr == NULL)
	{
		free(data.mlx_ptr);
		return ;
	}
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &key_press, &data);
	mlx_hook(data.win_ptr, 17, 0, &end, &data);
	mlx_loop(data.win_ptr);
	end(data);
}

void	print_img(t_data data, void *img, int x, int y)
{
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img,
		data->img.width * x, data->img.height * y);//a adapter
}