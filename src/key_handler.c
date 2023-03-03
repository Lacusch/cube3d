/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:17:30 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/03 10:46:26 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	handle_view(t_cube3d *data, enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_M)
		data->view_mode = 0;
	else if (key_pressed == MLX_KEY_N)
		data->view_mode = 1;
	return (draw_3d(data));
}

static void	add_rotation(t_cube3d *data, enum keys key_pressed)
{
	if (key_pressed == MLX_KEY_LEFT)
	{
		data->pa -= 0.1;
		if (data->pa < 0)
			data->pa += 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
	}
	else if (key_pressed == MLX_KEY_RIGHT)
	{
		data->pa += 0.1;
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

static void	handle_movement(t_cube3d *data)
{
	float	next_pos_a;
	float	next_pos_x;
	float	next_pos_y;
	char	c_map;

	next_pos_a = modify_pos_angle(data);
	next_pos_x = cos(next_pos_a) * (data->cube_size_x / 5);
	next_pos_y = sin(next_pos_a) * (data->cube_size_y / 5);
	c_map = keyh_read_map(data, next_pos_x * 3, next_pos_y * 3);
	if (c_map == '1' || c_map == ' ')
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
			|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
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
