/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:10 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 12:27:22 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	map_cube_size(t_cube3d *data)
{
	int	changed;
	int	player_pos_x;
	int	player_pos_y;

	changed = 0;
	player_pos_x = data->px / data->cube_size_x;
	player_pos_y = data->py / data->cube_size_y;
	if (data->s_width != (*data).mlx->width
		|| data->s_height != (*data).mlx->height)
	{
		data->s_width = (*data).mlx->width;
		data->s_height = (*data).mlx->height;
		changed = 1;
	}
	data->cube_size_x = (*data).mlx->width / data->map_size_x;
	data->cube_size_y = (*data).mlx->height / data->map_size_y;
	if (changed == 1)
	{
		data->px = player_pos_x * data->cube_size_x;
		data->px = data->px + data->cube_size_x / 2;
		data->py = player_pos_y * data->cube_size_y;
		data->py = data->py + data->cube_size_y / 2;
	}
	return (changed);
}
