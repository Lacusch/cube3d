#include "../includes/cube3d.h"

extern int	map_size_x;
extern int	map_size_y;

static void	paint_pixels(mlx_t *mlx, int i, int j, mlx_image_t *img, int is_wall)
{
	int	x;
	int	y;
	int	x_lim;
	int	y_lim;

	x = 0;
	y = 0;
	x_lim = mlx->width / map_size_x;
	y_lim = mlx->height / map_size_y;
	while (x < x_lim)
	{
		y = 0;
		while (y < y_lim)
		{
			if (is_wall)
				ft_pixel_put(img, (i * x_lim) + x, (j * y_lim) + y, 0xFFFFFFFF);
			else
				ft_pixel_put(img, (i * x_lim) + x, (j * y_lim) + y, 0x000000FF);
			y++;
		}
		x++;
	}
	return ;
}

void	draw_background(mlx_t *mlx, mlx_image_t *img, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_size_y)
	{
		x = 0;
		while (x < map_size_x)
		{
			if (map[y][x] == '1')
			{
				paint_pixels(mlx, x, y, img, 1);
			}
			else if (map[y][x] == '0' || map[y][x] == ' ' )
			{
				paint_pixels(mlx, x, y, img, 0);
			}
			x++;
		}
		y++;
	}
}
