// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* img;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
}

int32_t	main(int ac, char** av)
{
	t_cube3d	data;

	init_data(&data);
	if (check_arg(ac, av))
		return (1);
	// mlx_t* mlx;

	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	// 	return(EXIT_FAILURE);

	// img = mlx_new_image(mlx, 128, 128);
	// memset(img->pixels, 255, img->width * img->height * sizeof(int));
	// mlx_image_to_window(mlx, img, 0, 0);

	// mlx_loop_hook(mlx, &hook, mlx);
	// mlx_loop(mlx);

	// mlx_terminate(mlx);
	data_free(&data);
	return (EXIT_SUCCESS);
}
