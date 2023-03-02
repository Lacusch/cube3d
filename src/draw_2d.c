/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:33 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 02:14:35 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	paint_pixels(t_cube3d *d, int i, int j, int is_wall)
{
	int	x;
	int	y;
	int	x_lim;
	int	y_lim;

	x = 0;
	y = 0;
	x_lim = d->mlx->width / d->map_size_x;
	y_lim = d->mlx->height / d->map_size_y;
	while (x < x_lim)
	{
		y = 0;
		while (y < y_lim)
		{
			if (is_wall)
				ft_pixel_put(d->img, (i * x_lim) + x, (j * y_lim) + y, C_WHITE);
			else
				ft_pixel_put(d->img, (i * x_lim) + x, (j * y_lim) + y, C_BLACK);
			y++;
		}
		x++;
	}
	return ;
}

void	draw_background(t_cube3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_size_y)
	{
		x = 0;
		while (x < data->map_size_x)
		{
			if (data->map[y][x] == '1')
			{
				paint_pixels(data, x, y, 1);
			}
			else if (data->map[y][x] == '0' || data->map[y][x] == ' ' )
			{
				paint_pixels(data, x, y, 0);
			}
			x++;
		}
		y++;
	}
}
