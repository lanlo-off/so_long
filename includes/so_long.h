/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:40:01 by llechert          #+#    #+#             */
/*   Updated: 2025/07/10 11:58:20 by llechert         ###   ########.fr       */
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

typedef struct s_map
{
	char	*name;
	char	**dup;
	int		h_size;
	int		v_size;
	int		collec;
}	t_map;

#endif