#include "../includes/cube3d.h"

void	ft_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	int	bpp;
	int	max_size;
	int	x_sixe;
	int	y_size;

	if (x < 0 || x > (int)img->width)
		return ;
	if (y < 0 || y > (int)img->height)
		return ;
	bpp = sizeof(int32_t);
	max_size = img->width * img->height * 4;
	x_sixe = x * bpp;
	y_size = bpp * img->width * y;
	if ((x_sixe + y_size) > max_size)
		return ;
	ft_memset(img->pixels + (y_size) + x_sixe, get_r(color), 1);
	ft_memset(img->pixels + (y_size + 1) + x_sixe, get_g(color), 1);
	ft_memset(img->pixels + (y_size + 2) + x_sixe, get_b(color), 1);
	ft_memset(img->pixels + (y_size + 3) + x_sixe, get_a(color), 1);
}

void	ft_draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	delta_x = x1 - x0;
	delta_y = y1 - y0;
	pixel_x = x0;
	pixel_y = y0;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	while (pixels)
	{
		if (pixel_x < img->width && pixel_y < img->height)
			ft_pixel_put(img, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}
