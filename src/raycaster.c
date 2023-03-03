/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:55:07 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/03 12:15:30 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	set_ray_plane(t_cube3d *data, t_ray *ray, char dir)
{
	ray->rx = data->px;
	ray->ry = data->py;
	if (dir == 'h')
		ray->dof_h = data->map_size_x;
	else if (dir == 'v')
		ray->dof_v = data->map_size_y;
	return ;
}

void	cast_horizontal(t_cube3d *data, t_ray *ray)
{
	if (ray->ra < PI)
		set_ray_h_up(data, ray);
	if (ray->ra > PI)
		set_ray_h_down(data, ray);
	if (ray->ra == 0 || ray->ra == PI)
		set_ray_plane(data, ray, 'h');
	while (ray->dof_h < data->map_size_y)
		find_horizontal_hit(data, ray);
}

void	cast_vertical(t_cube3d *data, t_ray *ray)
{
	if (ray->ra > PI_HALF && ray->ra < PI3_HALF)
		set_ray_v_left(data, ray);
	if (ray->ra < PI_HALF || ray->ra > PI3_HALF)
		set_ray_v_right(data, ray);
	if (ray->ra == 0 || ray->ra == PI)
		set_ray_plane(data, ray, 'v');
	while (ray->dof_v < data->map_size_x)
		find_vertical_hit(data, ray);
}

void	wall_hit(t_cube3d *data, t_ray *ray)
{
	if (ray->dis_v < ray->dis_h)
	{
		if (ray->ra > PI_HALF && ray->ra < PI3_HALF)
			data->texture_tmp = data->texture_we;
		else
			data->texture_tmp = data->texture_ea;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->dis_t = ray->dis_v;
		ray->shade = 0;
	}
	if (ray->dis_h < ray->dis_v)
	{
		if (ray->ra >= 0 && ray->ra <= PI)
			data->texture_tmp = data->texture_so;
		else
			data->texture_tmp = data->texture_no;
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->dis_t = ray->dis_h;
		ray->shade = 1;
	}
}
