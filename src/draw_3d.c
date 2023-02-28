#include "../includes/cube3d.h"

void	draw_3d(t_cube3d *data)
{
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->screen_width, data->screen_height);
	if (data->view_mode == 1)
		draw_background(data);
	draw_rays_3d(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}