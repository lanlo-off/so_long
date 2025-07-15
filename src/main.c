/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:36:45 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 11:18:58 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 0);
	if (!init_struct(data, av))
		return (ft_putstr_fd("Could not initialize data structure\n", 2), 0);
	parser(data.map);//parse le nom et le contenu de la map, copie la map dans data->map et exit dans le parser si erreur
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit_handler(data, 1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, "solooooooong");//taille de window a faire dynamique selon taille de la map + mettre une limite a la taille de l'ecran
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
}

int	init_structure(t_data data, char **av)
{
	data.map = ft_calloc(1, sizeof(t_map));
	if (!data.map)
		return (0);
	data.map->name = av[1];
	data.img = ft_calloc(1, sizeof(t_img));
	if (!data.img)
		return (free(data.map), 0);
	data.mlx_ptr = 0;
	data.win_ptr = 0;
	data.width = 0;
	data.height = 0;
	data.tile_size = 64;//a ajuster avec les sprites
	return (1);
}
