#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

#define TILE_SIZE 64

typedef struct s_img {
	void	*wall;
	void	*floor;
}	t_img;

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	char	**map;
	int		width;
	int		height;
}	t_data;

// Petite map codée en dur
char	*test_map[] = {
	"11111",
	"10001",
	"10101",
	"10001",
	"11111",
	NULL
};

// Charge les sprites .xpm
int	init_images(t_data *data)
{
	int	w;
	int	h;

	data->img.wall = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/1_wall.xpm", &w, &h);
	data->img.floor = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/0_floor.xpm", &w, &h);
	if (!data->img.wall || !data->img.floor)
		return (0);
	return (1);
}

// Affiche la map
void	render_map(t_data *data)
{
	for (int i = 0; data->map[i]; i++)
	{
		for (int j = 0; data->map[i][j]; j++)
		{
			void *img = data->img.floor;
			if (data->map[i][j] == '1')
				img = data->img.wall;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img,
				j * TILE_SIZE, i * TILE_SIZE);
		}
	}
}

int	main(void)
{
	t_data	data;

	data.map = test_map;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);

	data.width = 5 * TILE_SIZE;
	data.height = 5 * TILE_SIZE;
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, "so_long mini");

	if (!init_images(&data))
		return (write(2, "Error loading images\n", 22), 1);

	render_map(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
