/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:08:10 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 14:48:41 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_map(t_map *map)
{
	int i;

	i = 0;
	while (i <= map->v_size)
	{
		printf("line %d : %s", i, map->map[i]);
		i++;
	}
	ft_putchar_fd('\n', 1);
	ft_putchar_fd('\n', 1);
}
