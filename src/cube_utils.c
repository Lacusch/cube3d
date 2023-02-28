#include "../includes/cube3d.h"

int map_cube_size(t_cube3d *data)
{
	int changed;
	int player_pos_x;
	int player_pos_y;

	changed = 0;
	player_pos_x = data->px / data->cube_size_x;
	player_pos_y = data->py / data->cube_size_y;
	if (data->screen_width != (*data).mlx->width || data->screen_height != (*data).mlx->height)
	{
		data->screen_width = (*data).mlx->width;
		data->screen_height = (*data).mlx->height;
		changed = 1;
	}
	data->cube_size_x = (*data).mlx->width / data->map_size_x;
	data->cube_size_y = (*data).mlx->height / data->map_size_y;
	if (changed == 1)
	{
		data->px = player_pos_x * data->cube_size_x;
		data->py = player_pos_y * data->cube_size_y;
	}
	return (changed);
}