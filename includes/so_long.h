/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:40:01 by llechert          #+#    #+#             */
/*   Updated: 2025/07/10 15:35:56 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

typedef struct s_game
{
	char	*name;
	char	**map;
	// char	**dup2;
	int		h_size;
	int		v_size;
	int		player;
	int		start_i;
	int		start_j;
	int		exit;
	int		exit_i;
	int		exit_j;
	int		collec;
}	t_game;

#endif