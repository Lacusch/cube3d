// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

#define WIDTH 1024
#define HEIGHT 512
#define PI 3.1415926535

static mlx_image_t* img;
static float pdx = 0;
static float pdy = 0;
static float pa = 0;

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
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 10;
		pdy = sin(pa) * 10;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 10;
		pdy = sin(pa) * 10;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		printf("w\n");
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		printf("s\n");
	printf("pdx: %f\n", pdx);
	printf("pdx: %f\n", pdy);
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
				ft_pixel_put(img, (i * 63) + x, (j * 63) + y, 0xFFFFFFFF);
			else 
				ft_pixel_put(img, (i * 63) + x, (j * 63) + y, 0x000000FF);
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
	res[2] = ft_strdup("10010001");
	res[3] = ft_strdup("10010001");
	res[4] = ft_strdup("10010001");
	res[5] = ft_strdup("10010001");
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
	
	init_data(&data);
	if (check_arg(ac, av))
		return (1);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (ft_error());
	map = muck_map();	
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_background(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	img = mlx_new_image(mlx, 8, 8);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	data_free(&data);
	return (EXIT_SUCCESS);
}
