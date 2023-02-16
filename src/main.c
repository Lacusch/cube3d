// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

#define WIDTH 600
#define HEIGHT 512
#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI /2

static mlx_image_t* img;
static float px = 0;
static float py = 0;
static float pdx = 0;
static float pdy = 0;
static float pa = 0;
static char	***map;

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
				ft_pixel_put(img, (j * 64) + y, (i * 64) + x, 0xFFFFFFFF);
			else 
				ft_pixel_put(img, (j * 64) + y, (i * 64) + x, 0x000000FF);
			y++;
		}
		x++;
	}
	return ;
}

static float dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((bx - ax) * (bx- ax)) + ((by - ay) * (by - ay))));
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
			}
			else
			{
				paint_pixels(i, j, img, 0);
			}
			j++;
		}
		// printf("\n");
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

static void	draw_user(void)
{
	ft_pixel_put(img, px, py, 0xFF0000FF);
}

static void draw_ray(void)
{
	ft_draw_line(img, px, py, px+pdx*20, py+pdy*20, 0x0000FFFF);
}

static void draw_rays_3d(void)
{
	int		r = 0;
	int 	mx;
	int 	my;
	int 	mp;
	int 	dof;
	float 	rx;
	float 	ry;
	float 	ra;
	float 	xo;
	float 	yo;
	float 	aTan;
	float	nTan;

	ra = pa;
	(void) aTan;
	(void) nTan;

	float disH;
	float disV;
	float hx;
	float vx;
	float hy;
	float vy;

	while (r < 1)
	{
		dof = 0;
		aTan = -1 / tan(ra);
		disH = 10000000;
		hx = px;
		hy = py;
		if (ra > PI)
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -(yo * aTan);
		}
		if (ra < PI)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = - (yo * aTan);
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			mp = my * 8 + mx;
			if (mp / 8 > 8)
				mp = 0;
			if (mp > 0 && mp < (8 * 8) && is_same_str(map[mp / 8][mp % 8], "1"))
			{
				hx = rx;
				hy = ry;
				disH = dist(px, py, hx, hy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
			if (rx < 0)
				rx = 0;
			if (ry < 0)
				ry = 0;
			if (rx > 512)
				rx = 512;
			if (ry > 512)
				ry = 512;
		}

		// vertical line

		dof = 0;
		nTan = -tan(ra);
		disV = 10000000;
		vx = px;
		vy = py;
		if (ra > P2 && ra < P3)
		{
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -(xo * nTan);
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)px >> 6) << 6) + 64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = - (xo * nTan);
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			mp = my * 8 + mx;
			if (mp / 8 > 8)
				mp = 0;
			if (mp > 0 && mp < (8 * 8) && is_same_str(map[mp / 8][mp % 8], "1"))
			{
				vx = rx;
				vy = ry;
				disV = dist(px, py, vx, vy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
			if (rx < 0)
				rx = 0;
			if (ry < 0)
				ry = 0;
			if (rx > 512)
				rx = 512;
			if (ry > 512)
				ry = 512;
		}
		if (disH > disV)
		{
			rx = hx;
			ry = hy;
		}
		else if (disV > disH)
		{
			rx = vx;
			ry = vy;
		}
		ft_draw_line(img, px, py, (int)rx, (int)ry, 0xFF0000FF);
		r++;
	}
}

void	draw(mlx_t	*mlx, char ***map)
{
	draw_background(img, map);
	draw_ray();
	draw_rays_3d();
	draw_user();
	mlx_image_to_window(mlx, img, 0, 0);
}

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		py -= 10;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		py += 10;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		px -= 10;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		px += 10;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	draw(mlx, map);
	return ;
}

int32_t	main(int ac, char** av)
{
	t_cube3d		data;
	mlx_t			*mlx;

	init_data(&data);
	map = muck_map();
	if (check_arg(ac, av))
		return (1);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
		return (ft_error());
	px = 300;
	py = 300;
	pdx = cos(pa);
	pdy = sin(pa);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw(mlx, map);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	data_free(&data);
	return (EXIT_SUCCESS);
}
