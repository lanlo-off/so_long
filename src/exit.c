/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:38:02 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 17:35:37 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	exit_init(t_data *data, int exit_code)
{
	free_tab_str(data->map->map);
	exit(exit_code);
	return (0);
}

int	exit_window(t_data *data, int exit_code)
{
	free(data->mlx_ptr);
	exit_init(data, exit_code);
	return (0);
}

int	exit_game(t_data *data, int exit_code)
{
	free(data->win_ptr);
	exit_window(data, exit_code);
	return (0);
}

int	end_nl(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (!len)
		return (0);
	return (line[len - 1] == '\n');
}