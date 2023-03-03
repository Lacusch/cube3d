/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_cast_t.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:52:55 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/03 12:16:35 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	cast_new_tx(t_cube3d *data, t_ray *ray)
{
	if (ray->shade == 1)
	{
		ray->tx = cast_int(data->texture_tmp->width * ray->rx);
		ray->tx = ray->tx / data->cube_size_x;
		ray->tx = cast_int(ray->tx) % data->texture_tmp->width;
	}
	else
	{
		ray->tx = cast_int(data->texture_tmp->height * ray->ry);
		ray->tx = ray->tx / data->cube_size_y;
		ray->tx = cast_int(ray->tx) % data->texture_tmp->height;
	}
}

static int	pixel_channel(t_cube3d *data, t_ray *ray, float ty, int pixel)
{
	int		bpp;
	int		pixel_int;
	int		pixel_color;

	bpp = sizeof(int32_t);
	pixel_int = bpp * cast_int(ty) * data->texture_tmp->height;
	pixel_int += (cast_int(ray->tx) * bpp);
	pixel_color = safe_get_pixel(data->texture_tmp, pixel_int + pixel);
	return (pixel_color);
}

static int	texture_pixel(t_cube3d *data, t_ray *ray, float ty)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = pixel_channel(data, ray, ty, 0);
	green = pixel_channel(data, ray, ty, 1);
	blue = pixel_channel(data, ray, ty, 2);
	alpha = pixel_channel(data, ray, ty, 3);
	return (get_rgba(red, green, blue, alpha));
}

void	cast_texture_to_screen(t_cube3d *data, t_ray *ray)
{
	int		y;
	int		pixel;
	float	ty;
	float	ty_step;

	y = 0;
	ty_step = data->texture_tmp->height / ray->line_h;
	ty = ty_step;
	cast_new_tx(data, ray);
	while (y < ray->line_h)
	{
		pixel = texture_pixel(data, ray, ty);
		ft_pixel_put(data->img, ray->r, ray->line_offset + y, pixel);
		ty += ty_step;
		y++;
	}
}
