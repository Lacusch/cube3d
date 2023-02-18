// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

#define WIDTH 1024
#define HEIGHT 512
#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI /2
#define DR PI/180

static mlx_image_t* img;
static int map_size_x = 0;
static int map_size_y = 0;	
static float px = 0;
static float py = 0;
static float pdx = 0;
static float pdy = 0;
static float pa = 0;
static char	**map;

static int ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

static void paint_pixels(int i, int j, mlx_image_t* img, int is_wall)
{
	int x;
	int	y;
	int	x_lim;
	int y_lim;

	x = 0;
	y = 0;
	x_lim = WIDTH / 2 / map_size_x;
	y_lim = HEIGHT / map_size_y;
	while (x < x_lim)
	{ 
		y = 0;
		while (y < y_lim)
		{
			if (is_wall)
				ft_pixel_put(img, (i * x_lim) + x, (j * y_lim) + y, 0xFFFFFFFF);
			else 
				ft_pixel_put(img, (i * x_lim) + x, (j * y_lim) + y, 0x000000FF);
			y++;
		}
		x++;
	}
	return ;
}

static void draw_background(mlx_image_t* img, char **map)
{
	int x;
	int y;

	y = 0;
	(void) img;
	while (y < map_size_y)
	{
		x = 0;
		while (x < map_size_x)
		{
			if (map[y][x] == '1')
			{
				paint_pixels(x, y, img, 1);
			}
			else if (map[y][x] == '0')
			{
				paint_pixels(x, y, img, 0);
			}
			x++;
		}
		y++;
	}
}

static void clear_3d_img(mlx_image_t* img)
{
	int x;
	int y;

	y = 0;
	(void) img;
	while (y < map_size_y)
	{
		x = 0;
		while (x < map_size_x)
		{
			paint_pixels(x + map_size_x, y, img, 0);
			x++;
		}
		y++;
	}
}

static char	**muck_map(void)
{
	char	**res;

	res = malloc(sizeof(char **) * (map_size_y + 1));
	res[0] = "11111111";
	res[1] = "10010001";
	res[2] = "10010111";
	res[3] = "10010001";
	res[4] = "10010001";
	res[5] = "10000001";
	res[6] = "10101001";
	res[7] = "11111111";
	res[8] = NULL;
	return (res);
}

static void	draw_user(void)
{
	ft_pixel_put(img, px, py, 0x0000FF20);
	ft_pixel_put(img, px - 1, py, 0x0000FF20);
	ft_pixel_put(img, px + 1, py, 0x0000FF20);
	ft_pixel_put(img, px, py + 1, 0x0000FF20);
	ft_pixel_put(img, px, py - 1, 0x0000FF20);
}

static void draw_ray(void)
{
	ft_draw_line(img, px, py, px + (pdx * 1), py + (pdy * 1), 0x00FF0040);
}

static float dist(float ax, float ay, float bx, float by)
{

	float a;
	float b;

	a = (bx - ax) * (bx- ax);
	b = (by - ay) * (by - ay);
	return (sqrt(a + b));
}

static void draw_rays_3d(void)
{
	int		r = 0;
	int		iter = 0;
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
	float	disT;
	float	lineH;
	float	lineO;
	float	ca;

	ra = pa - (DR * 30);
	if (ra < 0)
		ra += (2 * PI);
	if (ra > (2 * PI))
		ra -= (2 * PI);
	(void) aTan;
	(void) nTan;

	float disH;
	float hx;
	float hy;

	float disV;
	float vx;	
	float vy;

	while (r < 60)
	{
		dof = 0;
		iter = 0;
		aTan = -1 / tan(ra);
		disH = 1000000;
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
			if (mp > 0 && mp < (8 * 8) && (map[mp / 8][mp % 8] == '1'))
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
		}
		// vertical line

		dof = 0;
		nTan = -tan(ra);
		disV = 1000000;
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
			if (mp > 0 && mp < (8 * 8) && (map[mp / 8][mp % 8] == '1'))
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
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		else if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}
		ft_draw_line(img, px, py, (int)rx, (int)ry, 0x00FF0001);
		// draw 3d
		ca = pa - ra;
		if (ca < 0)
			ca += (2 * PI);
		if (ca > (2 * PI))
			ca -= (2 * PI);
		disT = disT * cos(ca);
		lineH = (64 * 320) / disT;
		if (lineH > 320)
			lineH = 320;
		lineO = 160 - lineH / 2;
		while (iter < 8)
		{
			ft_draw_line(img, (r * 8) + iter + 530, lineO, (r * 8) + iter + 530, lineH + lineO, 0xFF0000FF);
			iter++; 
		}
		ra += DR;
		if (ra < 0)
			ra += (2 * PI);
		if (ra > (2 * PI))
			ra -= (2 * PI);
		r++;
	}
}

void	draw(mlx_t	*mlx)
{
	draw_background(img, map);
	clear_3d_img(img);
	draw_rays_3d();
	draw_ray();
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
		pa -= 0.05;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		pa += 0.05;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa);
		pdy = sin(pa);
	}
	draw(mlx);
	return ;
}

int32_t	main(int ac, char** av)
{
	t_cube3d		data;
	mlx_t			*mlx;

	init_data(&data);
	map_size_y = 8;
	map_size_x = 8;
	map = muck_map();
	if (check_arg(ac, av))
		return (1);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
		return (ft_error());
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	px = mlx->width / 2 / 2;
	py = mlx->height / 2;
	pdx = cos(pa) * 2;
	pdy = sin(pa) * 2;
	draw(mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	data_free(&data);
	return (EXIT_SUCCESS);
}
