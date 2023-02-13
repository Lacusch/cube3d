#include "../includes/cube3d.h"

// Get the red channel.
static int get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
static int get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
static int get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
static int get_a(int rgba)
{
	return (rgba & 0xFF);
}

void    ft_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	int BPP;

	BPP = sizeof(int32_t);
	ft_memset(img->pixels + (BPP * img->width * y) + (x * BPP), get_r(color), 1);
	ft_memset(img->pixels + (BPP * img->width * y + 1)+ (x * BPP), get_g(color), 1);
	ft_memset(img->pixels + (BPP * img->width * y + 2)+ (x * BPP), get_b(color), 1);
	ft_memset(img->pixels + (BPP * img->width * y + 3)+ (x * BPP), get_a(color), 1);
}