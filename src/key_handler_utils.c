/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:32:03 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 12:18:25 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	pos_setter(float pos, float incr, int div)
{
	return ((int)(pos + incr) / div);
}

char	keyh_read_map(t_cube3d *data, float x, float y)
{
	int	map_y;
	int	map_x;

	map_y = pos_setter(data->py, y, data->cube_size_y);
	map_x = pos_setter(data->px, x, data->cube_size_x);
	return (safe_map_read(data, map_y, map_x));
}

float	modify_pos_angle(t_cube3d *data)
{
	float	new_angle;

	new_angle = data->pa;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		new_angle += PI;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		new_angle -= PI / 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		new_angle += PI / 2;
	reset_360(&new_angle);
	return (new_angle);
}
