#include "../includes/cube3d.h"

extern mlx_image_t *g_img;
extern int g_width;
extern int g_height;
extern int g_mode;
extern char **g_map;

void	draw_3d(mlx_t	*mlx)
{
	mlx_delete_image(mlx, g_img);
	g_img = mlx_new_image(mlx, g_width, g_height);
	if (g_mode == 1)
		draw_background(mlx, g_img, g_map);
	draw_rays_3d(mlx);
	mlx_image_to_window(mlx, g_img, 0, 0);
}