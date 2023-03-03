/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 04:29:49 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/03 12:12:19 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	handle_fish_eye(t_cube3d *data, t_ray *ray)
{
	ray->ca = data->pa - ray->ra;
	reset_360(&(ray)->ca);
	ray->dis_t = ray->dis_t * cos(ray->ca);
}

static void	ray_to_screen(t_cube3d *data, t_ray *ray)
{
	ray->tx = 0;
	ray->line_h = (data->cube_size_y * data->mlx->height * 0.66) / ray->dis_t;
	ray->line_offset = data->mlx->height * 0.35 - ray->line_h / 2;
}

static void	ft_draw_3d_line(t_cube3d *data, t_ray *ray)
{
	handle_fish_eye(data, ray);
	ray_to_screen(data, ray);
	draw_ceiling(data, ray);
	draw_floor(data, ray);
	cast_texture_to_screen(data, ray);
}

void	draw_rays_3d(t_cube3d *data)
{
	t_ray	ray;
	t_line	line;

	init_rays(data, &ray);
	while (ray.r < data->mlx->width)
	{
		init_ray(data, &ray);
		cast_horizontal(data, &ray);
		cast_vertical(data, &ray);
		wall_hit(data, &ray);
		if (data->view_mode == 1)
		{
			line = new_line(data->px, data->py, ray.rx, ray.ry);
			ft_draw_line(data->img, line, C_GREEN);
		}
		else
			ft_draw_3d_line(data, &ray);
		ray.ra += (DEGREE / (data->mlx->width / 60));
		reset_360(&ray.ra);
		ray.r++;
	}
}
