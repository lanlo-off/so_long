/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:40:01 by llechert          #+#    #+#             */
/*   Updated: 2025/07/15 11:40:48 by llechert         ###   ########.fr       */
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
	t_map	*map;
	t_img	*img;
	int		tile_size;
	int		width;
	int		height;
}	t_data;

typedef struct s_map
{
	char	*name;
	char	**map;
	int		h_size;
	int		v_size;
	int		player;
	int		start_i;
	int		start_j;
	int		exit;
	int		exit_i;
	int		exit_j;
	int		collec;
}	t_map;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
}	t_img;

/*error.c*/
void	exit_handler(t_data data, int exit_code);

/*graphics.c*/
void	render_map(t_data data, t_map *map);
void	print_img(t_data data, void *img, int i, int j);

/*init_tiles.c*/
void	init_images(t_data data);

/*main.c*/
int		init_structure(t_data data, char **av);

/*parser_utils.c*/
int		check_map_characteristics(t_map *map);
int		check_outlines(t_map *map);
int		count_spe_tiles(t_map *map);
int		invalid_char(t_map *map, char c, int i, int j);
int		valid_path(t_map *map);

/*parser.c*/
void	parser(t_map *map);
int		parse_name(char *name);
int		parse_map(t_map *map);
int		check_size(t_map *map, int fd);
int		duplicate_map(t_map *map, int fd);

/*path_finding.c*/
void	flood_fill(t_map *map, int i, int j);
int		process_target(char c);
void	reverse_flood(t_map *map, int i, int j);
int		rev_process_target(char c);
int		found_way(char **map);

#endif