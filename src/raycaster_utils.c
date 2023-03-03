/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 03:27:16 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/03 10:52:15 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	set_ray_h_down(t_cube3d *data, t_ray *ray)
{
	ray->ry = cast_int(data->py / data->cube_size_y);
	ray->ry = ray->ry * data->cube_size_y - F_PRECISION;
	ray->rx = (data->py - ray->ry) * ray->ang_tan + data->px;
	ray->yo = data->cube_size_y * -1;
	ray->xo = ray->yo * ray->ang_tan * -1;
}

void	set_ray_h_up(t_cube3d *data, t_ray *ray)
{
	ray->ry = cast_int(data->py / data->cube_size_y);
	ray->ry = ray->ry * data->cube_size_y + data->cube_size_y;
	ray->rx = (data->py - ray->ry) * ray->ang_tan + data->px;
	ray->yo = data->cube_size_y;
	ray->xo = ray->yo * ray->ang_tan * -1;
}

void	set_ray_v_left(t_cube3d *data, t_ray *ray)
{
	ray->rx = cast_int(data->px / data->cube_size_x);
	ray->rx = ray->rx * data->cube_size_x - F_PRECISION;
	ray->ry = (data->px - ray->rx) * ray->inv_tan + data->py;
	ray->xo = data->cube_size_x * -1;
	ray->yo = ray->xo * ray->inv_tan * -1;
}

void	set_ray_v_right(t_cube3d *data, t_ray *ray)
{
	ray->rx = cast_int(data->px / data->cube_size_x);
	ray->rx = ray->rx * data->cube_size_x + data->cube_size_x;
	ray->ry = (data->px - ray->rx) * ray->inv_tan + data->py;
	ray->xo = data->cube_size_x;
	ray->yo = ray->xo * ray->inv_tan * -1;
}
