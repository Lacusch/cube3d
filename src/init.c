/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:23:41 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 12:23:25 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	init_map(t_cube3d *data)
{
	data->map_size_x = 0;
	data->map_size_y = 0;
	data->cube_size_x = 0;
	data->cube_size_y = 0;
	data->s_width = 2000;
	data->s_height = 1280;
	data->px = 0;
	data->py = 0;
	data->pdx = 0;
	data->pdy = 0;
	data->pa = 0;
	data->view_mode = 0;
	data->img = NULL;
	data->texture_we = NULL;
	data->texture_ea = NULL;
	data->texture_so = NULL;
	data->texture_no = NULL;
	data->texture_tmp = NULL;
	data->mlx = NULL;
}

void	init_data(t_cube3d *data)
{
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->input_error = false;
	data->start = '\0';
	data->f_color[0] = -1;
	data->f_color[1] = -1;
	data->f_color[2] = -1;
	data->c_color[0] = -1;
	data->c_color[1] = -1;
	data->c_color[2] = -1;
	data->map_data.height = -1;
	data->map_data.width = -1;
	data->player.x = -1;
	data->player.y = -1;
	init_map(data);
}

void	init_position(t_cube3d *data)
{
	data->px = (data->player.x * data->cube_size_x);
	data->px = data->px + data->cube_size_x / 2;
	data->py = (data->player.y * data->cube_size_y);
	data->py = data->py + data->cube_size_y / 2;
	data->pdx = cos(data->pa);
	data->pdy = sin(data->pa);
	if (data->start == 'N')
		data->pa = -PI_HALF - DEGREE;
	else if (data->start == 'S')
		data->pa = PI_HALF - DEGREE;
	else if (data->start == 'E')
		data->pa = 0 + DEGREE;
	else if (data->start == 'W')
		data->pa = PI - DEGREE;
}
