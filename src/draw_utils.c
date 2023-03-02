/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:15:09 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 14:33:04 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	int	bpp;
	int	max_size;
	int	x_sixe;
	int	y_size;

	if (x < 0 || x >= (int)img->width)
		return ;
	if (y < 0 || y >= (int)img->height)
		return ;
	bpp = sizeof(int32_t);
	max_size = img->width * img->height * 4;
	x_sixe = x * bpp;
	y_size = bpp * img->width * y;
	if ((x_sixe + y_size + 3) >= max_size)
		return ;
	ft_memset(img->pixels + (y_size) + x_sixe, get_r(color), 1);
	ft_memset(img->pixels + (y_size + 1) + x_sixe, get_g(color), 1);
	ft_memset(img->pixels + (y_size + 2) + x_sixe, get_b(color), 1);
	ft_memset(img->pixels + (y_size + 3) + x_sixe, get_a(color), 1);
}

void	ft_draw_line(mlx_image_t *img, t_line line, int color)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	delta_x = line.x1 - line.x0;
	delta_y = line.y1 - line.y0;
	pixel_x = line.x0;
	pixel_y = line.y0;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	while (pixels > 0)
	{
		if (pixel_x < img->width && pixel_y < img->height)
			ft_pixel_put(img, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

t_line	new_line(int x0, int y0, int x1, int y1)
{
	t_line	line;

	line.x0 = x0;
	line.y0 = y0;
	line.x1 = x1;
	line.y1 = y1;
	return (line);
}
