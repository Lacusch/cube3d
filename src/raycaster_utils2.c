/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 04:03:16 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/03 12:15:24 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	is_wall_hit(t_cube3d *data, t_ray *ray)
{
	if ((ray->mx >= 0 && ray->mx < data->map_size_x)
		&& (ray->my >= 0 && ray->my < data->map_size_y)
		&& ((safe_map_read(data, ray->my, ray->mx) == '1')))
		return (1);
	return (0);
}

void	find_horizontal_hit(t_cube3d *data, t_ray *ray)
{
	ray->mx = cast_int(ray->rx / data->cube_size_x);
	ray->my = cast_int(ray->ry / data->cube_size_y);
	if (is_wall_hit(data, ray))
	{
		ray->hx = ray->rx;
		ray->hy = ray->ry;
		ray->dis_h = hyp_dist(data->px, data->py, ray->hx, ray->hy);
		ray->dof_h = data->map_size_y;
	}
	else
	{
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->dof_h += 1;
	}
}

void	find_vertical_hit(t_cube3d *data, t_ray *ray)
{
	ray->mx = cast_int(ray->rx / data->cube_size_x);
	ray->my = cast_int(ray->ry / data->cube_size_y);
	if (is_wall_hit(data, ray))
	{
		ray->vx = ray->rx;
		ray->vy = ray->ry;
		ray->dis_v = hyp_dist(data->px, data->py, ray->vx, ray->vy);
		ray->dof_v = data->map_size_x;
	}
	else
	{
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->dof_v += 1;
	}
}
