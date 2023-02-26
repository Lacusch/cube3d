#include "../includes/cube3d.h"

extern int		g_mode;
extern char		**g_map;
extern int		g_cube_size_x;
extern int		g_cube_size_y;
extern float	g_px;
extern float	g_py;
extern float	g_pa;
extern float	g_pdx;
extern float	g_pdy;

static void	handle_view(mlx_t *mlx, enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_M)
		g_mode = 0;
	else if (key_pressed == MLX_KEY_N)
		g_mode = 1;
	return (draw(mlx));
}

static void	add_rotation(mlx_t *mlx, enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_LEFT)
	{
		g_pa -= 0.1;
		if (g_pa < 0)
			g_pa += 2 * PI;
		g_pdx = cos(g_pa) * 5;
		g_pdy = sin(g_pa) * 5;
	}
	else if (key_pressed == MLX_KEY_RIGHT)
	{
		g_pa += 0.1;
		if (g_pa > 2 * PI)
			g_pa -= 2 * PI;
		g_pdx = cos(g_pa) * 5;
		g_pdy = sin(g_pa) * 5;
	}
	return (draw(mlx));
}

static int	valid_movement(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W)
		|| mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_D)
		|| mlx_is_key_down(mlx, MLX_KEY_A)
		|| mlx_is_key_down(mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		return (1);
	return (0);
}

static int	pos_setter(float pos, float incr, int div)
{
	return ((int)(pos + incr) / div);
}

static void	handle_movement(mlx_t *mlx)
{
	float	next_pos_a;
	float	next_pos_x;
	float	next_pos_y;
	char	c_map;

	next_pos_a = g_pa;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		next_pos_a += PI;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		next_pos_a -= PI / 2;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		next_pos_a += PI / 2;
	reset_360(&next_pos_a);
	next_pos_x = cos(next_pos_a) * (g_cube_size_x / 4);
	next_pos_y = sin(next_pos_a) * (g_cube_size_y / 4);
	c_map = g_map[pos_setter(g_py, next_pos_y, g_cube_size_y)][pos_setter(g_px, next_pos_x, g_cube_size_x)];
	if (c_map == '1' || c_map == ' ')
	{
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			return (draw(mlx));
		return ;
	}
	g_px += next_pos_x;
	g_py += next_pos_y;
	return (draw(mlx));
}

void	hook(void *param)
{
	mlx_t		*mlx;	

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		return (mlx_close_window(mlx));
	if (mlx_is_key_down(mlx, MLX_KEY_N))
		return (handle_view(mlx, MLX_KEY_N));
	if (mlx_is_key_down(mlx, MLX_KEY_M))
		return (handle_view(mlx, MLX_KEY_M));
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		return (add_rotation(mlx, MLX_KEY_LEFT));
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		return (add_rotation(mlx, MLX_KEY_RIGHT));
	if (valid_movement(mlx))
		return (handle_movement(mlx));
	if (map_cube_size(mlx))
		return (draw(mlx));
	return ;
}
