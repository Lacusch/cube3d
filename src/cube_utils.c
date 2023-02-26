#include "../includes/cube3d.h"

extern int g_width;
extern int g_height;
extern float g_px;
extern float g_py;
extern int g_cube_size_x;
extern int g_cube_size_y;
extern int g_map_size_x;
extern int g_map_size_y;

int map_cube_size(mlx_t *mlx)
{
	int changed;
	int player_pos_x;
	int player_pos_y;

	changed = 0;
	player_pos_x = g_px / g_cube_size_x;
	player_pos_y = g_py / g_cube_size_y;
	if (g_width != mlx->width || g_height != mlx->height)
	{
		g_width = mlx->width;
		g_height = mlx->height;
		changed = 1;
	}
	g_cube_size_x = mlx->width / g_map_size_x;
	g_cube_size_y = mlx->height / g_map_size_y;
	if (changed == 1)
	{
		g_px = player_pos_x * g_cube_size_x;
		g_py = player_pos_y * g_cube_size_y;
	}
	return (changed);
}