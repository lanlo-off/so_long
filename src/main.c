/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:36:45 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 17:37:28 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 0);
	if (!init_structure(&data, av))//verifier qu'on initialise bien tout
		return (ft_putstr_fd("Could not initialize data structure\n", 2), 0);
	parser(data.map);//parse le nom et le contenu de la map, copie la map dans data->map et exit dans le parser si erreur
	fill_data(&data);
	if (data.width > 1600 || data.height > 900)
	{
		ft_putstr_fd("Map is too big\n", 2);
		exit_init(&data, 1);
	}
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit_init(&data, 1);
	start_game(&data);
}

int	init_structure(t_data *data, char **av)
{
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		return (0);
	data->map->name = av[1];
	data->mlx_ptr = 0;
	data->win_ptr = 0;
	data->width = 0;
	data->height = 0;
	data->tile_size = 64;//a ajuster avec les sprites
	data->collected = 0;
	data->moves = 0;
	return (1);
}

void	fill_data(t_data *data)
{
	data->width = data->map->h_size * data->tile_size;
	data->height = data->map->v_size * data->tile_size;
	data->player_i = data->map->start_i;
	data->player_j = data->map->start_j;
}