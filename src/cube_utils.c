#include "../includes/cube3d.h"

extern int g_width;
extern int g_height;
extern float px;
extern float py;
extern int cube_size_x;
extern int cube_size_y;
extern int map_size_x;
extern int map_size_y;

int map_cube_size(mlx_t *mlx)
{
	int changed;
	int player_pos_x;
	int player_pos_y;

	changed = 0;
	player_pos_x = px / cube_size_x;
	player_pos_y = py / cube_size_y;
	if (g_width != mlx->width || g_height != mlx->height)
	{
		g_width = mlx->width;
		g_height = mlx->height;
		changed = 1;
	}
	cube_size_x = mlx->width / map_size_x;
	cube_size_y = mlx->height / map_size_y;
	if (changed == 1)
	{
		px = player_pos_x * cube_size_x;
		py = player_pos_y * cube_size_y;
	}
	return (changed);
}