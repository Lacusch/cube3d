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
static float px = 0;
static float py = 0;
static float pdx = 0;
static float pdy = 0;
static float pa = 0;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		py -= 5;
		// img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		py += 5;
		// img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		px -= 5;
		// img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		px += 5;
		// img->instances[0].x += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		printf("w\n");
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		printf("s\n");
	ft_draw_line(img, px, py, pdx, pdy, 0x00FF00FF);
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
				ft_pixel_put(img, (j * 63) + y, (i * 63) + x, 0xFFFFFFFF);
			else 
				ft_pixel_put(img, (j * 63) + y, (i * 63) + x, 0x000000FF);
			y++;
		}
		x++;
	}
	return ;
}

static void draw_background(mlx_image_t* img, char ***map)
{
	int i;
	int j;

	i = 0;
	(void) img;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (is_same_str(map[i][j], "1"))
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

static char	***muck_map(void)
{
	char	***res;
	int		map_size;

	map_size = 8;
	res = malloc(sizeof(char **) * (map_size + 1));
	res[0] = ft_split("1,1,1,1,1,1,1,1", ',');
	res[1] = ft_split("1,0,1,1,1,1,0,1", ',');
	res[2] = ft_split("1,0,0,1,1,0,0,1", ',');
	res[3] = ft_split("1,0,0,1,1,0,0,1", ',');
	res[4] = ft_split("1,0,0,0,0,0,0,1", ',');
	res[5] = ft_split("1,0,0,0,0,0,0,1", ',');
	res[6] = ft_split("1,0,0,0,0,0,0,1", ',');
	res[7] = ft_split("1,1,1,1,1,1,1,1", ',');
	res[8] = NULL;
	return (res);
}

void	draw(mlx_t	*mlx)
{
	char	***map;

	map = muck_map();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	px = 256;
	py = 256;
	pdx = 256;
	pdy = 256;
	draw_background(img, map);
	// ft_draw_line(img, px, py, pdx, pdy, 0x00FF00FF);
	// raycasting(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
}

int32_t	main(int ac, char** av)
{
	t_cube3d		data;
	mlx_t			*mlx;
	
	
	init_data(&data);
	if (check_arg(ac, av))
		return (1);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
		return (ft_error());
	draw(mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	data_free(&data);
	return (EXIT_SUCCESS);
}
