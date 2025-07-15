/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:36:45 by llechert          #+#    #+#             */
/*   Updated: 2025/07/11 15:08:54 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Wrong number of arguments", 2), 0);
	init_struct(data, av);
	parser(data.game);//parse le nom (repo/nom.ber avec nom non-vide)
	//exit dans le parser
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit_handler(data, 1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, "solooooooong");//taille de window a faire dynamique selon taille de la map + mettre une limite a la taille de l'ecran
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
}

void	init_structure(t_data data, char **av)
{
	t_game	*game;
	
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->name = av[1];
	
}