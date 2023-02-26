#include "../includes/cube3d.h"
 
int get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int get_a(int rgba)
{
	return (rgba & 0xFF);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void    ft_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	int BPP;
	int max_size;

	BPP = sizeof(int32_t);
	if (x < 0 || x > (int)img->width)
		return ;
	if (y < 0 || y > (int)img->height)
		return ;
	max_size = img->width * img->height * 4;
	if ((int)((BPP * img->width * y) + (x * BPP)) > max_size)
		return ;
	ft_memset(img->pixels + (BPP * img->width * y) + (x * BPP), get_r(color), 1);
	ft_memset(img->pixels + (BPP * img->width * y + 1)+ (x * BPP), get_g(color), 1);
	ft_memset(img->pixels + (BPP * img->width * y + 2)+ (x * BPP), get_b(color), 1);
	ft_memset(img->pixels + (BPP * img->width * y + 3)+ (x * BPP), get_a(color), 1);
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
