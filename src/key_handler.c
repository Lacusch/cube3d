#include "../includes/cube3d.h"

extern int mode;
extern char **map;
extern int cube_size_x;
extern int cube_size_y;
extern float px;
extern float py;
extern float pa;
extern float pdx;
extern float pdy;

enum keys key_pressed_type(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		 return (MLX_KEY_ESCAPE);
	else if (mlx_is_key_down(mlx, MLX_KEY_M))
		 return (MLX_KEY_M);
	else if (mlx_is_key_down(mlx, MLX_KEY_N))
		return (MLX_KEY_N);
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
		return (MLX_KEY_W);
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		return (MLX_KEY_S);
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		return (MLX_KEY_D);
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		return (MLX_KEY_A);
	else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		return (MLX_KEY_LEFT);
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		return (MLX_KEY_RIGHT);
	return (MLX_KEY_SPACE);
}

static void handle_23D_view(enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_M)
		mode = 0;
	else if (key_pressed == MLX_KEY_N)
		mode = 1;
}

static float handle_movement_alpha(enum keys key)
{
	float pa_cpy;

	pa_cpy = pa;
	if (key == MLX_KEY_S)
		pa_cpy += PI;
	if (key == MLX_KEY_A)
		pa_cpy -= PI / 2;
	if (key == MLX_KEY_D)
		pa_cpy += PI / 2;
	if (pa_cpy < 0)
		pa_cpy += (2 * PI);
	if (pa_cpy > (2 * PI))
		pa_cpy -= (2 * PI);
	return (pa_cpy);
}

static void add_step(int x, int y)
{
	px += x;
	py += y;
}

static void add_rotation(enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_LEFT)
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	else if (key_pressed == MLX_KEY_RIGHT)
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	return ;
}


void hook(void* param)
{
	mlx_t		*mlx;
	enum keys 	key_pressed;
	float		next_pos_a;
	float		next_pos_x;
	float		next_pos_y;

	mlx = param;
	key_pressed = key_pressed_type(mlx);
	if (key_pressed == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
	if (key_pressed == MLX_KEY_LEFT ||
		key_pressed == MLX_KEY_RIGHT)
			add_rotation(key_pressed);
	if (key_pressed == MLX_KEY_N || 
		key_pressed == MLX_KEY_M)
		{
			handle_23D_view(key_pressed);
			draw(mlx);
		}
	next_pos_a = handle_movement_alpha(key_pressed);
	next_pos_x = cos(next_pos_a) * (cube_size_x / 4);
	next_pos_y = sin(next_pos_a) * (cube_size_y / 4);
	if (map[(int)(((py + next_pos_y) / cube_size_y))][(int)(((px + next_pos_x) / cube_size_x))] == '1' 
		|| map[(int)(((py + next_pos_y) / cube_size_y))][(int)(((px + next_pos_x) / cube_size_x))] == ' ')
		{
			if (key_pressed == MLX_KEY_LEFT ||
				key_pressed == MLX_KEY_RIGHT)
					draw(mlx);
			return ;
		}
	if (mlx_is_key_down(mlx, MLX_KEY_M))
		mode = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_N))
		mode = 1;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		add_step(next_pos_x, next_pos_y);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		add_step(next_pos_x, next_pos_y);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		add_step(next_pos_x, next_pos_y);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		add_step(next_pos_x, next_pos_y);
	if (mlx_is_key_down(mlx, MLX_KEY_M) ||
		mlx_is_key_down(mlx, MLX_KEY_N) ||
		mlx_is_key_down(mlx, MLX_KEY_W) ||
		mlx_is_key_down(mlx, MLX_KEY_S) ||
		mlx_is_key_down(mlx, MLX_KEY_A) ||
		mlx_is_key_down(mlx, MLX_KEY_D) ||
		mlx_is_key_down(mlx, MLX_KEY_LEFT) ||
		mlx_is_key_down(mlx, MLX_KEY_RIGHT) ||
		map_cube_size(mlx))
		draw(mlx);
	return ;
}