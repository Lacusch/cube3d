/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:55:33 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 03:14:55 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_rays(t_cube3d *data, t_ray *ray)
{
	ray->r = 0;
	ray->iter = 0;
	ray->shade = 1;
	ray->ra = data->pa - DEGREE * 30;
	reset_360(&(ray)->ra);
}

void	init_ray(t_cube3d *data, t_ray *ray)
{
	ray->rx = 0;
	ray->ry = 0;
	ray->iter = 0;
	ray->dof_h = 0;
	ray->dof_v = 0;
	ray->aTan = -1 / tan(ray->ra);
	ray->nTan = -tan(ray->ra);
	ray->hx = data->px;
	ray->hy = data->py;
	ray->vx = data->px;
	ray->vy = data->py;
	ray->disH = 1000000;
	ray->disV = 1000000;
}
