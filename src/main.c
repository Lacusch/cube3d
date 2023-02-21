// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

#define WIDTH 1680
#define HEIGHT 1020
#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI /2
#define DR PI / 180

static mlx_image_t* img;
static int map_size_x = 0;
static int map_size_y = 0;
static int cube_size_x = 0;
static int cube_size_y = 0;
static int g_width = 0;
static int g_height = 0;
static int wall_color = 0;
static float px = 0;
static float py = 0;
static float pdx = 0;
static float pdy = 0;
static float pa = 0;
static char	**map;
static int	mode = 0;

static int ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

static int map_cube_size(mlx_t *mlx)
{
	int changed;

	changed = 0;
	printf("mlx->width: %i - mlx->height: %i\n", mlx->width, mlx->height);
	if (g_width != mlx->width || g_height != mlx->height)
	{
		g_width = mlx->width;
		g_height = mlx->height;
		mlx_delete_image(mlx, img);
		img = mlx_new_image(mlx, mlx->width, mlx->height);
		changed = 1;
	}
	cube_size_x = mlx->width /  map_size_x;
	cube_size_y = mlx->height / map_size_y;
	return (changed);
}

static void paint_pixels(mlx_t *mlx, int i, int j, mlx_image_t* img, int is_wall)
{
	int x;
	int	y;
	int	x_lim;
	int y_lim;

	x = 0;
	y = 0;
	x_lim = mlx->width / map_size_x;
	y_lim = mlx->height / map_size_y;
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

static void draw_background(mlx_t *mlx, mlx_image_t* img, char **map)
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
				paint_pixels(mlx, x, y, img, 1);
			}
			else if (map[y][x] == '0' || map[y][x] == ' ' )
			{
				paint_pixels(mlx, x, y, img, 0);
			}
			x++;
		}
		y++;
	}
}

static char	**muck_map(void)
{
	char	**res;

	res = malloc(sizeof(char **) * (map_size_y + 1));
	res[0] = "1111111111111111111111111111111111111111";
	res[1] = "1000000000000000000000000000000000000001";
	res[2] = "1000000000000000000000000000000000000001";
	res[3] = "1000000000000000000000000000000000000001";
	res[4] = "1000000000000000000000000000000000000001";
	res[5] = "1000000000000000000000000000000000000001";
	res[6] = "1000000000000000000000000000000000000001";
	res[7] = "1000000000000000000000000000000000000001";
	res[8] = "1000000000000000000000000000000000000001";
	res[9] = "1000000000000000000000000000000000000001";
	res[10] = "1000000000000000000000000000000000000001";
	res[11] = "1000000000000000000000000000000000000001";
	res[12] = "1000000000000000000000000000000000000001";
	res[13] = "1000000000000000000000000000000000000001";
	res[14] = "1000000000000000000000000000000000000001";
	res[15] = "1000000000000000000000000000000000000001";
	res[16] = "1000000000000000000000000000000000000001";
	res[17] = "1000000000000000000000000000000000000001";
	res[18] = "1000000000000000000000000000000000000001";
	res[19] = "1000000000000000001000000000000000000001";
	res[20] = "1000000000000000000000000000000000000001";
	res[21] = "1000000000000000000000000000000000000001";
	res[22] = "1000000000000000000000000000000000000001";
	res[23] = "1000000000000000000000000000000000000001";
	res[24] = "1000000000000000000000000000000000000001";
	res[25] = "1000000000000000000000000000000000000001";
	res[26] = "1000000000000000000000000000000000000001";
	res[27] = "1000000000000000000000000000000000000001";
	res[28] = "1000000000000000000000000000000000000001";
	res[29] = "1000000000000000000000000000000000000001";
	res[30] = "1000000000000000000000000000000000000001";
	res[31] = "1000000000000000000000000000000000000001";
	res[32] = "1000000000000000000000000000000000000001";
	res[33] = "1000000000000000000000000000000000000001";
	res[34] = "1000000000000000000000000000000000000001";
	res[35] = "1000000000000000000000000000000000000001";
	res[36] = "1000000000000000000000000000000000000001";
	res[37] = "1000000000000000000000000000000000000001";
	res[38] = "1000000000000000000000000000000000000001";
	res[39] = "1111111111111111111111111111111111111111";
	res[40] = NULL;
	return (res);
}

// static void	draw_user(void)
// {
// 	ft_pixel_put(img, px, py, 0x0000FF20);
// 	ft_pixel_put(img, px - 1, py, 0x0000FF20);
// 	ft_pixel_put(img, px + 1, py, 0x0000FF20);
// 	ft_pixel_put(img, px, py + 1, 0x0000FF20);
// 	ft_pixel_put(img, px, py - 1, 0x0000FF20);
// }

// static void draw_ray(void)
// {
// 	ft_draw_line(img, px, py, px + (pdx * 1), py + (pdy * 1), 0x00FF0040);
// }

static float dist(float ax, float ay, float bx, float by)
{
	float a;
	float b;

	a = (bx - ax) * (bx- ax);
	b = (by - ay) * (by - ay);
	return (sqrt(a + b));
}

static void draw_rays_3d(mlx_t *mlx)
{
	int		r = 0;
	int		iter = 0;
	int 	mx;
	int 	my;
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

	ra = pa - DR * 30;
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

	while (r < 600)
	{
		dof = 0;
		iter = 0;
		aTan = -1 / tan(ra);
		disH = 1000000;
		hx = px;
		hy = py;
		vx = px;
		vy = py;

		// horizontal line
		if (ra > PI)
		{
			ry = (((int)py / cube_size_y) * cube_size_y) - 0.0001;
			rx = (py - ry) * aTan + px;
			yo = - cube_size_y;
			xo = - (yo * aTan);
		}
		if (ra < PI)
		{
			ry = (((int)py / cube_size_y) * cube_size_y) + cube_size_y;
			rx = (py - ry) * aTan + px;
			yo = cube_size_y;
			xo = - (yo * aTan);
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = map_size_x;
		}
		while (dof < map_size_x)
		{
			mx = (int)rx / cube_size_x;
			my = (int)ry / cube_size_y;
			if ((mx >= 0 && mx < map_size_x) && (my >= 0 && my < map_size_y) && (map[my][mx] == '1'))
			{
				hx = rx;
				hy = ry;
				disH = dist(px, py, hx, hy);
				dof = map_size_x;
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
		if (ra > P2 && ra < P3)
		{
			rx = (((int)px / cube_size_x) * cube_size_x) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = - cube_size_x;
			yo = - (xo * nTan);
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)px / cube_size_x) * cube_size_x) + cube_size_x;
			ry = (px - rx) * nTan + py;
			xo = cube_size_x;
			yo = - (xo * nTan);
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = map_size_y;
		}
		while (dof < map_size_y)
		{
			mx = (int)rx / cube_size_x;
			my = (int)ry / cube_size_y;
			if ((mx >= 0 && mx < map_size_x) && (my >= 0 && my < map_size_y) && (map[my][mx] == '1'))
			{
				vx = rx;
				vy = ry;
				disV = dist(px, py, vx, vy);
				dof = map_size_y;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			} 
		}
		// vertical wall hit
		if (disV < disH)
		{
			if (ra > P2 && ra < P3)
				wall_color = 0xA020F0FF;   // purple
			else 
				wall_color = 0xFF2E2EFF;   // red
			rx = vx;
			ry = vy;
			disT = disV;
		}
		// horizontal wall hit
		else if (disH < disV)
		{
			if (ra >= 0 && ra <= PI)
				wall_color = 0xFFFF00FF;  // yellow 
			else
				wall_color = 0x00FF00FF;  // green
			rx = hx;
			ry = hy;
			disT = disH;
		}
		if (mode == 1)	
			ft_draw_line(img, px, py, (int)rx, (int)ry, 0x00FF0001);
		(void) ca;
		(void) lineH;
		(void) lineO;
		// ------------------------------

		// draw 3d
		// FIX FISHEYE
		ca = pa - ra;
		if (ca < 0)
			ca += (2 * PI);
		if (ca > (2 * PI))
			ca -= (2 * PI);
		disT = disT * cos(ca);
		lineH = (cube_size_y * mlx->height * 0.625) / disT;
		if (lineH > mlx->height)
		{
			lineH = mlx->height;
			lineO = 0;
		}
		else
			lineO = mlx->height * 0.35 - lineH/2;
		int iter_len = mlx->width / 600;
		
		while(iter < iter_len)
		{
			if (mode == 0)
			{
				ft_draw_line(img, (r * iter_len) + iter, 0, (r * iter_len) + iter, lineO, 0x87CEEB);
				ft_draw_line(img, (r * iter_len) + iter, lineO, (r * iter_len) + iter, lineH + lineO, wall_color);
				ft_draw_line(img, (r * iter_len) + iter, mlx->width, (r * iter_len) + iter, lineO + lineH, 0x808080FF);
			}
			iter++;
		}
		ra += DR / 10;
		if (ra < 0)
			ra += (2 * PI);
		if (ra > (2 * PI))
			ra -= (2 * PI);
		r++;
	}
}

void	draw(mlx_t	*mlx)
{
	ft_memset(img->pixels, 0, mlx->width * mlx->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	if (mode == 1)
		draw_background(mlx, img, map);
	draw_rays_3d(mlx);
	mlx_image_to_window(mlx, img, 0, 0);
}

static void handle_movement(enum keys key)
{
	float co;
	float ca;
	float pa_cpy;

	pa_cpy = pa;
	if (key == MLX_KEY_S)
		pa_cpy += PI;
	if (key == MLX_KEY_A)
		pa_cpy -= PI / 2;
	if (key == MLX_KEY_D)
		pa_cpy += PI / 2;
	if (pa_cpy < 0)
		pa_cpy += (2 * PI);
	if (pa_cpy > (2 * PI))
		pa_cpy -= (2 * PI);
	co = sin(pa_cpy);
	ca = cos(pa_cpy);
	px += ca * 20;
	py += co * 20; 
}


void hook(void* param)
{
	mlx_t* mlx = param;

	printf("listening from hook\n");
	if (mlx_is_key_down(mlx, MLX_KEY_M))
		mode = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_N))
		mode = 1;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		handle_movement(MLX_KEY_W);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		handle_movement(MLX_KEY_S);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		handle_movement(MLX_KEY_A);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		handle_movement(MLX_KEY_D);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		pa -= 0.05;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		pa += 0.05;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_M) ||
		mlx_is_key_down(mlx, MLX_KEY_N) ||
		mlx_is_key_down(mlx, MLX_KEY_W) ||
		mlx_is_key_down(mlx, MLX_KEY_S) ||
		mlx_is_key_down(mlx, MLX_KEY_A) ||
		mlx_is_key_down(mlx, MLX_KEY_D) ||
		mlx_is_key_down(mlx, MLX_KEY_LEFT) ||
		mlx_is_key_down(mlx, MLX_KEY_RIGHT) || map_cube_size(mlx))
		draw(mlx);
	return ;
}

int32_t	main(int ac, char** av)
{
	t_cube3d		data;
	mlx_t			*mlx;

	init_data(&data);
	map_size_y = 40;
	map_size_x = 40;
	g_width = WIDTH;
	g_height = HEIGHT;
	map = muck_map();
	if (check_arg(ac, av))
		return (1);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
		return (ft_error());
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	map_cube_size(mlx);
	printf("%i x %i\n", cube_size_x, cube_size_y);
	pa = 0;
	px = mlx->width / 2;
	py = mlx->height / 2;
	pdx = cos(pa);
	pdy = sin(pa);
	draw(mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	data_free(&data);
	return (EXIT_SUCCESS);
}
