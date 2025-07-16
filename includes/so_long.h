/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llechert <llechert@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:40:01 by llechert          #+#    #+#             */
/*   Updated: 2025/07/16 12:45:36 by llechert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

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

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
	int		tile_size;
	int		width;
	int		height;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
	int		collected;
	int		moves;
	int		player_i;
	int		player_j;
}	t_data;

/*empty.c*/
void	print_map(t_map *map);

/*exit.c*/
int		exit_init(t_data *data, int exit_code);
int		exit_window(t_data *data, int exit_code);
int		exit_game(t_data *data, int exit_code);

/*game.c*/
void	start_game(t_data *data);
void	move_player(t_data *data, int di, int dj);
int		handle_keypress(int keycode, t_data *data);
void	print_move(int moves);

/*graphics.c*/
void	render_map(t_data *data, t_map *map);
void	print_img(t_data *data, void *img, int i, int j);
int		init_images(t_data *data);

/*main.c*/
int		init_structure(t_data *data, char **av);
void	fill_data(t_data *data);

/*miscellaneous.c*/
char	*skip_nl(int fd);
int		end_nl(char *line);
void	free_gnl_buffer(int fd);

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
int		process_target(char *c);
void	reverse_flood(t_map *map, int i, int j);
int		rev_process_target(char *c);
int		found_way(char **map);

#endif