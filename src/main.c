// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <memory.h>
#include "../includes/cube3d.h"

mlx_image_t			*g_img;
mlx_texture_t 		*g_texture_we;
mlx_texture_t		*g_texture_ea;
mlx_texture_t		*g_texture_so;
mlx_texture_t		*g_texture_no;
mlx_texture_t		*g_tmp;
int 				g_map_size_x = 0;
int 				g_map_size_y = 0;
int 				g_cube_size_x = 0;
int 				g_cube_size_y = 0;
int 				g_width = 0;
int 				g_height = 0;
float 				g_px = 0;
float 				g_py = 0;
float 				g_pdx = 0;
float 				g_pdy = 0;
float 				g_pa = 0;
char				**g_map;
int					g_mode = 0;

static int ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

static char	safe_map_read(char **map, int x, int y)
{
	if (x > g_map_size_x || y > g_map_size_y)
		return (' ');
	return (map[x][y]);
}

static char	**muck_map(void)
{
	char	**res;

	res = malloc(sizeof(char **) * (g_map_size_y + 1));
	res[0] = "111111111111111111111111111111";
	res[1] = "100000000000000000000000000001";
	res[2] = "100000000000000000000000000001";
	res[3] = "100000000000000000000000000001";
	res[4] = "100000000000000000000000000001";
	res[5] = "100000000000000000000000000001";
	res[6] = "100000000000000000000000000001";
	res[7] = "100000000000N00000000000000001";
	res[8] = "100000000000000000000000000001";
	res[9] = "100000000000000000000000000001";
	res[10] = "100000000000000000000000000001";
	res[11] = "100000000000000000000000000001";
	res[12] = "100000000000000000000000000001";
	res[13] = "100000000000000000000000000001";
	res[14] = "100000000000000000000000000001";
	res[15] = "100000000000011111111111111111";
	res[16] = "100000000000011000000000000001";
	res[17] = "100000000000000000000000000001";
	res[18] = "100000000000000000000000000001";
	res[19] = "100000000000000000000000000001";
	res[20] = "100000000000000000000000000001";
	res[21] = "100000000000000000000000000001";
	res[22] = "100000000000000000000000000001";
	res[23] = "100000000000000000000000000001";
	res[24] = "100000000000000000000000000001";
	res[25] = "100000000000000000000000000001";
	res[26] = "100000000000000000000000000001";
	res[27] = "100000000000000000000000000001";
	res[28] = "100000000000000000000000000001";
	res[29] = "111111111111111111111111111111";
	res[30] = NULL;
	return (res);
}

static float dist(float ax, float ay, float bx, float by)
{
	float a;
	float b;

	a = (bx - ax) * (bx- ax);
	b = (by - ay) * (by - ay);
	return (sqrt(a + b));
}

static int sget_pixel(mlx_texture_t *texture, int pixel)
{
	int BPP;
	int max_allowed;
	BPP = sizeof(int32_t);

	max_allowed = texture->width * texture->height * 4;
	if (pixel > max_allowed)
		return 0;
	return (texture->pixels[pixel]);
}

static void draw_rays_3d(mlx_t *mlx)
{
	int		r = 0;
	float		iter = 0;
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
	int		shade = 1;

	ra = g_pa - DEGREE * 30;
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

	while (r < mlx->width)
	{
		dof = 0;
		iter = 0;
		aTan = -1 / tan(ra);
		disH = 1000000;
		hx = g_px;
		hy = g_py;
		vx = g_px;
		vy = g_py;

		// horizontal line
		if (ra > PI)
		{
			ry = (((int)g_py / g_cube_size_y) * g_cube_size_y) - 0.0001;
			rx = (g_py - ry) * aTan + g_px;
			yo = - g_cube_size_y;
			xo = - (yo * aTan);
		}
		if (ra < PI)
		{
			ry = (((int)g_py / g_cube_size_y) * g_cube_size_y) + g_cube_size_y;
			rx = (g_py - ry) * aTan + g_px;
			yo = g_cube_size_y;
			xo = - (yo * aTan);
		}
		if (ra == 0 || ra == PI)
		{
			rx = g_px;
			ry = g_py;
			dof = g_map_size_x;
		}
		while (dof < g_map_size_x)
		{
			mx = (int)rx / g_cube_size_x;
			my = (int)ry / g_cube_size_y;
			if ((mx >= 0 && mx < g_map_size_x) && (my >= 0 && my < g_map_size_y) && (g_map[my][mx] == '1'))
			{
				hx = rx;
				hy = ry;
				disH = dist(g_px, g_py, hx, hy);
				dof = g_map_size_x;
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
			rx = (((int)g_px / g_cube_size_x) * g_cube_size_x) - 0.0001;
			ry = (g_px - rx) * nTan + g_py;
			xo = - g_cube_size_x;
			yo = - (xo * nTan);
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)g_px / g_cube_size_x) * g_cube_size_x) + g_cube_size_x;
			ry = (g_px - rx) * nTan + g_py;
			xo = g_cube_size_x;
			yo = - (xo * nTan);
		}
		if (ra == 0 || ra == PI)
		{
			rx = g_px;
			ry = g_py;
			dof = g_map_size_y;
		}
		while (dof < g_map_size_y)
		{
			mx = (int)rx / g_cube_size_x;
			my = (int)ry / g_cube_size_y;
			if ((mx >= 0 && mx < g_map_size_x) && (my >= 0 && my < g_map_size_y) && ((safe_map_read(g_map, my, mx) == '1') || (safe_map_read(g_map, my, mx) == ' ')))
			{
				vx = rx;
				vy = ry;
				disV = dist(g_px, g_py, vx, vy);
				dof = g_map_size_y;
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
				g_tmp = g_texture_we;
			else 
				g_tmp = g_texture_ea;
			rx = vx;
			ry = vy;
			disT = disV;
			shade = 0;
		}
		// horizontal wall hit
		else if (disH < disV)
		{
			if (ra >= 0 && ra <= PI)
				g_tmp = g_texture_so;
			else
				g_tmp = g_texture_no;
				rx = hx;
				ry = hy;
				disT = disH;
				shade = 1;
			}
		if (g_mode == 1)	
			ft_draw_line(g_img, g_px, g_py, (int)rx, (int)ry, 0x00FF00FF);
		else
		{
			// ----------------------------
			// draw 3d
			// FIX FISHEYE
			ca = g_pa - ra;
			if (ca < 0)
				ca += (2 * PI);
			if (ca > (2 * PI))
				ca -= (2 * PI);
			disT = disT * cos(ca);
			// End fish eye
			lineH = (g_cube_size_y * mlx->height * 0.66) / disT;
			float tx = 0;
			lineO = mlx->height * 0.35 - lineH / 2;
			// -- Ray iterations
			int iter_len = mlx->width / mlx->width;
			// DRAW VERTICAL LINESs
			while (iter < iter_len)
			{
				ft_draw_line(g_img, (r * iter_len) + iter, 0, (r * iter_len) + iter, lineO, 0x87CEEB); // ceiling
				ft_draw_line(g_img, (r * iter_len) + iter, mlx->width, (r * iter_len) + iter, lineO + lineH, 0x808080FF); // floor
				// Mapping to texture
				int y = 0;
				float ty_step = g_tmp->height / lineH;
				float ty = ty_step;
				if (shade == 1)
					tx = (int)((g_tmp->width * rx) / g_cube_size_x) % g_tmp->width;
				else
					tx = (int)((g_tmp->height * ry) / g_cube_size_y) % g_tmp->height;
				while (y < lineH)
				{
					int BPP;
					BPP = sizeof(int32_t);
					int rc = sget_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)tx * BPP)) + 0);
					int gc = sget_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)tx * BPP)) + 1);
					int bc = sget_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)tx * BPP)) + 2);
					int ac = sget_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)tx * BPP)) + 3);
					ft_pixel_put(g_img, (r * iter_len) + iter, lineO + y, get_rgba(rc, gc, bc, ac));
					ty += ty_step;
					y++;
				}
				iter++;
			}
		}
		// incrementing deegree
		ra += DEGREE / (mlx->width / 60);
		// Looping in a circle 
		if (ra < 0)
			ra += (2 * PI);
		if (ra > (2 * PI))
			ra -= (2 * PI);
		r++;
	}
}

void	draw(mlx_t	*mlx)
{
	mlx_delete_image(mlx, g_img);
	g_img = mlx_new_image(mlx, g_width, g_height);
	if (g_mode == 1)
		draw_background(mlx, g_img, g_map);
	draw_rays_3d(mlx);
	mlx_image_to_window(mlx, g_img, 0, 0);
}

int32_t	main(int ac, char** av)
{
	t_cube3d		data;
	mlx_t			*mlx;

	init_data(&data);
	g_map_size_y = 30;
	g_map_size_x = 30;
	g_width = 1680;
	g_height = 1280;
	g_map = muck_map();
	if (check_arg(ac, av))
		return (1);
	if (!(mlx = mlx_init(g_width, g_height, "CUB3D", true)))
		return (ft_error());
	g_img = mlx_new_image(mlx, g_width, g_height);
	if (!g_img)
		perror("Error creating img");
	map_cube_size(mlx);
	g_pa = 0;
	g_px = 2 * g_cube_size_x;
	g_py = 2 * g_cube_size_y;
	g_pdx = cos(g_pa);
	g_pdy = sin(g_pa);
	g_texture_we = mlx_load_png("./textures/eagle.png");
	g_texture_ea = mlx_load_png("./textures/brick.png");
	g_texture_so = mlx_load_png("./textures/greystone.png");
	g_texture_no = mlx_load_png("./textures/wood.png");
	draw(mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	data_free(&data);
	return (EXIT_SUCCESS);
}
