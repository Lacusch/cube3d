// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

#define WIDTH 1024
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

static int ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

static void paint_pixels(int i, int j, mlx_image_t* img, int is_wall)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (x < 64)
	{
		y = 0;
		while (y < 64)
		{
			if (is_wall)
				mlx_put_pixel(img, (i * 63) + x, (j * 63) + y, 0xFFFFFFFF);
			else 
				mlx_put_pixel(img, (i * 63) + x, (j * 63) + y, 0x000000FF);
			y++;
		}
		x++;
	}
	return ;
}

static void draw_background(mlx_image_t* img, char **map)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (map[j][i] == '1')
			{
				paint_pixels(i, j, img, 1);
				printf("1");
			}
			else
			{
				printf("0");
				paint_pixels(i, j, img, 0);
			}
			j++;
		}
		printf("\n");
		i++;
	}
}

static char	**muck_map(void)
{
	char	**res;

	res = malloc(sizeof(char *) * 9);
	res[0] = ft_strdup("11111111");
	res[1] = ft_strdup("10000001");
	res[2] = ft_strdup("10011101");
	res[3] = ft_strdup("10000001");
	res[4] = ft_strdup("10000001");
	res[5] = ft_strdup("10000001");
	res[6] = ft_strdup("10000001");
	res[7] = ft_strdup("11111111");
	res[8] = NULL;
	return (res);
}

int32_t	main(int ac, char** av)
{
	t_cube3d		data;
	mlx_t*			mlx;
	char 			**map;
	
	// mlx_texture_t*	texture;

	init_data(&data);
	if (check_arg(ac, av))
		return (1);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (ft_error());

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	map = muck_map();
	mlx_image_to_window(mlx, img, 0, 0);
	draw_background(img, map);
	img = mlx_new_image(mlx, 8, 8);
	ft_memset(img->pixels, 0x000000FF, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, WIDTH/3, HEIGHT/2);

	// mlx_put_pixel(img, i, j, 0xFF0000FF);
	// texture = mlx_load_png("./textures/wood.png");
	// if (!texture)
    //     return (ft_error());
	// img = mlx_texture_to_image(mlx, texture);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	data_free(&data);

	return (EXIT_SUCCESS);
}
