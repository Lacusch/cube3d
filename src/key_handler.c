#include "../includes/cube3d.h"

static void	handle_view(t_cube3d *data, enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_M)
		data->view_mode = 0;
	else if (key_pressed == MLX_KEY_N)
		data->view_mode  = 1;
	return (draw_3d(data));
}

static void	add_rotation(t_cube3d *data, enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_LEFT)
	{
		data->pa -= 0.05;
		if (data->pa < 0)
			data->pa += 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
	}
	else if (key_pressed == MLX_KEY_RIGHT)
	{
		data->pa += 0.05;
		if (data->pa > 2 * PI)
			data->pa -= 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
	}
	return (draw_3d(data));
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

static void	handle_movement(t_cube3d *data)
{
	float	next_pos_a;
	float	next_pos_x;
	float	next_pos_y;
	char	c_map;

	next_pos_a = data->pa;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		next_pos_a += PI;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		next_pos_a -= PI / 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		next_pos_a += PI / 2;
	reset_360(&next_pos_a);
	next_pos_x = cos(next_pos_a) * (data->cube_size_x / 10);
	next_pos_y = sin(next_pos_a) * (data->cube_size_y / 10);
	c_map = data->map[pos_setter(data->py, next_pos_y, data->cube_size_y)][pos_setter(data->px, next_pos_x, data->cube_size_x)];
	if (c_map == '1' || c_map == ' ')
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			return (draw_3d(data));
		return ;
	}
	data->px += next_pos_x;
	data->py += next_pos_y;
	return (draw_3d(data));
}

void	hook(void *param)
{
	t_cube3d	*data;	

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		return (mlx_close_window(data->mlx));
	if (mlx_is_key_down(data->mlx, MLX_KEY_N))
		return (handle_view(data, MLX_KEY_N));
	if (mlx_is_key_down(data->mlx, MLX_KEY_M))
		return (handle_view(data, MLX_KEY_M));
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		return (add_rotation(data, MLX_KEY_LEFT));
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		return (add_rotation(data, MLX_KEY_RIGHT));
	if (valid_movement(data->mlx))
		return (handle_movement(data));
	if (map_cube_size(data))
		return (draw_3d(data));
	return ;
}
