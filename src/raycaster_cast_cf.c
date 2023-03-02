/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cast_cf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:55:01 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 06:26:02 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_ceiling(t_cube3d *data, t_ray *ray)
{
	t_line	line;
	int		color;

	line = new_line(ray->r, 0, ray->r, ray->lineO);
	color = get_rgba(data->c_color[0], data->c_color[1], data->c_color[2], 255);
	ft_draw_line(data->img, line, color);
}

void	draw_floor(t_cube3d *data, t_ray *ray)
{
	t_line	line;
	int		color;

	line = new_line(ray->r, data->mlx->width, ray->r, ray->lineO + ray->lineH);
	color = get_rgba(data->f_color[0], data->f_color[1], data->f_color[2], 255);
	ft_draw_line(data->img, line, color);
}
