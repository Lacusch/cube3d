// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

#define WIDTH 1920
#define HEIGHT 1080

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

// static int ft_error(void)
// {
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	return (EXIT_FAILURE);
// }

int32_t	main(int ac, char** av)
{
	t_cube3d		data;
	// mlx_t*			mlx;
	// mlx_texture_t*	texture;

	init_data(&data);
	if (check_arg(ac, av))
		return (EXIT_FAILURE);
	input_data(&data, av[1]);
	if (data.input_error)
		return (EXIT_FAILURE);
	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	// 	return (ft_error());
	// img = mlx_new_image(mlx, 128, 128);
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	// mlx_image_to_window(mlx, img, 0, 0);
	// texture = mlx_load_png("./textures/wood.png");
	// if (!texture)
    //     return (ft_error());
	// img = mlx_texture_to_image(mlx, texture);
	// mlx_image_to_window(mlx, img, 0, 0);
	// mlx_loop_hook(mlx, &hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	//doubble free, need to debug
	data_free(&data);
	system("leaks cub3D");
	return (EXIT_SUCCESS);
}
