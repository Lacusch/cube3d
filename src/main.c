// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "../includes/cube3d.h"

t_cube3d			data;
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

void draw_rays_3d(mlx_t *mlx)
{
	t_rays	rays;

	rays.r = 0;
	rays.iter = 0;
	rays.shade = 1;
	rays.ra = g_pa - DEGREE * 30;
	reset_360(&rays.ra);
	while (rays.r < mlx->width)
	{
		// printf("here\n");
		rays.dof = 0;
		rays.iter = 0;
		rays.aTan = -1 / tan(rays.ra);
		rays.disH = 1000000;
		rays.hx = g_px;
		rays.hy = g_py;
		rays.vx = g_px;
		rays.vy = g_py;

		// horizontal line -------
		if (rays.ra > PI)
		{
			rays.ry = (((int)(g_py / g_cube_size_y)) * g_cube_size_y) - 0.0001;
			rays.rx = (g_py - rays.ry) * rays.aTan + g_px;
			rays.yo = - g_cube_size_y;
			rays.xo = - (rays.yo * rays.aTan);
		}
		if (rays.ra < PI)
		{
			rays.ry = (((int)(g_py / g_cube_size_y)) * g_cube_size_y) + g_cube_size_y;
			rays.rx = (g_py - rays.ry) * rays.aTan + g_px;
			rays.yo = g_cube_size_y;
			rays.xo = - (rays.yo * rays.aTan);
		}
		if (rays.ra == 0 || rays.ra == PI)
		{
			rays.rx = g_px;
			rays.ry = g_py;
			rays.dof = g_map_size_x;
		}
		while (rays.dof < g_map_size_x)
		{
			rays.mx = (int)(rays.rx / g_cube_size_x);
			rays.my = (int)(rays.ry / g_cube_size_y);
			if ((rays.mx >= 0 && rays.mx < g_map_size_x) && (rays.my >= 0 && rays.my < g_map_size_y) && ((safe_map_read(g_map, rays.my, rays.mx) == '1')))
			{
				rays.hx = rays.rx;
				rays.hy = rays.ry;
				rays.disH = hyp_dist(g_px, g_py, rays.hx, rays.hy);
				rays.dof = g_map_size_x;
			}
			else
			{
				rays.rx += rays.xo;
				rays.ry += rays.yo;
				rays.dof += 1;
			}
		}
		// ft_draw_line(g_img, g_px, g_py, (int)rays.rx, (int)rays.ry, 0x00FF00FF);
		// vertical line |
		rays.dof = 0;
		rays.nTan = -tan(rays.ra);
		rays.disV = 1000000;
		rays.rx = 0;
		rays.ry = 0;
		if (rays.ra > P2 && rays.ra < P3)
		{
			// printf("rays.ra > P2 && rays.ra < P3 \n");
			rays.rx = (((int)(g_px / g_cube_size_x)) * g_cube_size_x) - 0.0001;
			rays.ry = (g_px - rays.rx) * rays.nTan + g_py;
			rays.xo = -g_cube_size_x;
			rays.yo = - (rays.xo * rays.nTan);
		}
		if (rays.ra < P2 || rays.ra > P3)
		{
			// printf("rays.ra < P2 || rays.ra > P3 \n");
			rays.rx = (((int)(g_px / g_cube_size_x)) * g_cube_size_x) + g_cube_size_x; 
			rays.ry = (g_px - rays.rx) * rays.nTan + g_py;
			rays.xo = g_cube_size_x;
			rays.yo = - (rays.xo * rays.nTan);
		}
		if (rays.ra == 0 || rays.ra == PI)
		{
			// printf("asdfjasdkhfasdfhdsajkfksjdhfkjsflds\n");
			rays.rx = g_px;
			rays.ry = g_py;
			rays.dof = g_map_size_y;
		}
		// printf("g_map_size_y: %i\n", g_map_size_y);
		// printf("vf - ray.y :%i - rays.x: %i\n", rays.my, rays.mx);
		while (rays.dof < g_map_size_x)
		{
			// printf("1\n");
			rays.mx = (int)(rays.rx / g_cube_size_x);
			rays.my = (int)(rays.ry / g_cube_size_y);
			// printf("pp - ray.y :%i - rays.x: %i\n", rays.my, rays.mx);
			if ((rays.mx >= 0 && rays.mx < g_map_size_x) && (rays.my >= 0 && rays.my < g_map_size_y) && ((safe_map_read(g_map, rays.my, rays.mx) == '1')))
			{
				// printf("entre ray.y :%i - rays.x: %i\n", rays.my, rays.mx);
				rays.vx = rays.rx;
				rays.vy = rays.ry;
				rays.disV = hyp_dist(g_px, g_py, rays.vx, rays.vy);
				rays.dof = g_map_size_x;
			}
			else
			{
				rays.rx += rays.xo;
				rays.ry += rays.yo;
				rays.dof += 1;
			}
			// printf("dof: %i\n", rays.dof);
		}
		// ft_draw_line(g_img, g_px, g_py, (int)rays.rx, (int)rays.ry, 0xFF0000FF);
		// vertical wall hit
		if (rays.disV < rays.disH)
		{
			if (rays.ra > P2 && rays.ra < P3)
				g_tmp = g_texture_we;
			else
				g_tmp = g_texture_ea;
			rays.rx = rays.vx;
			rays.ry = rays.vy;
			rays.disT = rays.disV;
			rays.shade = 0;
		}
		// horizontal wall hit
		else if (rays.disH < rays.disV)
		{
			if (rays.ra >= 0 && rays.ra <= PI)
				g_tmp = g_texture_so;
			else
				g_tmp = g_texture_no;
			rays.rx = rays.hx;
			rays.ry = rays.hy;
			rays.disT = rays.disH;
			rays.shade = 1;
		}
		else 
		{	
			// rays.rx += 0.01;
			// rays.ry += 0.01;
		}
		if (g_mode == 1)
		{
			ft_draw_line(g_img, g_px, g_py, (int)rays.rx, (int)rays.ry, 0x00FF00FF);
		}
		else
		{
			// ----------------------------
			// draw 3d
			// FIX FISHEYE
			rays.ca = g_pa - rays.ra;
			if (rays.ca < 0)
				rays.ca += (2 * PI);
			if (rays.ca > (2 * PI))
				rays.ca -= (2 * PI);
			rays.disT = rays.disT * cos(rays.ca);
			// End fish eye
			rays.lineH = (g_cube_size_y * mlx->height * 0.66) / rays.disT;
			rays.tx = 0;
			rays.lineO = mlx->height * 0.35 - rays.lineH / 2;
			// -- Ray iterations
			int iter_len = mlx->width / mlx->width;
			// DRAW VERTICAL LINESs
			while (rays.iter < iter_len)
			{
				ft_draw_line(g_img, (rays.r * iter_len) + rays.iter, 0, (rays.r * iter_len) + rays.iter, rays.lineO, get_rgba(data.c_color[0], data.c_color[1], data.c_color[2], 255)); // ceiling
				ft_draw_line(g_img, (rays.r * iter_len) + rays.iter, mlx->width, (rays.r * iter_len) + rays.iter, rays.lineO + rays.lineH, get_rgba(data.f_color[0], data.f_color[1], data.f_color[2], 255)); // floor
				// Mapping to texture
				int y = 0;
				float ty_step = g_tmp->height / rays.lineH;
				float ty = ty_step;
				if (rays.shade == 1)
					rays.tx = (int)((g_tmp->width * rays.rx) / g_cube_size_x) % g_tmp->width;
				else
					rays.tx = (int)((g_tmp->height * rays.ry) / g_cube_size_y) % g_tmp->height;
				while (y < rays.lineH)
				{
					int BPP;
					BPP = sizeof(int32_t);
					int rc = safe_get_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)rays.tx * BPP)) + 0);
					int gc = safe_get_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)rays.tx * BPP)) + 1);
					int bc = safe_get_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)rays.tx * BPP)) + 2);
					int ac = safe_get_pixel(g_tmp, (BPP * (((int)ty) * g_tmp->height) + ((int)rays.tx * BPP)) + 3);
					ft_pixel_put(g_img, (rays.r * iter_len) + rays.iter, rays.lineO + y, get_rgba(rc, gc, bc, ac));
					ty += ty_step;
					y++;
				}
				rays.iter++;
			}
		}
		// incrementing deegree
		rays.ra += (DEGREE / (mlx->width / 60));
		// rays.ra += DEGREE;
		// Looping in a circle
		reset_360(&rays.ra);
		rays.r++;
	}
}

int32_t	main(int ac, char** av)
{
	mlx_t			*mlx;

	init_data(&data);
	if (check_arg(ac, av))
	{
		// system("leaks cub3D");
		return (EXIT_FAILURE);
	}
	input_data(&data, av[1]);
	if (data.input_error)
	{
		data_free(&data);
		// system("leaks cub3D");
		return (EXIT_FAILURE);
	}
	data_printf(&data);
	g_map_size_y = data.map_data.height;
    g_map_size_x = data.map_data.width;
	// g_map_size_y = 30;
	// g_map_size_x = 30;
    g_width = 1680;
    g_height = 1280;
    g_map = data.map;
    // g_map = muck_map();
	if (!(mlx = mlx_init(g_width, g_height, "CUB3D", true)))
    		return (ft_error());
    	g_img = mlx_new_image(mlx, g_width, g_height);
    	if (!g_img)
    		perror("Error creating img");
    	map_cube_size(mlx);
    g_mode = 1;
	g_pa = 0;
    // if (data.start == 'N')
    // 	g_pa = -P2 - DEGREE;
	// else if (data.start == 'S')
	// 	g_pa = P2 - DEGREE;
	// else if (data.start == 'E')
	// 	g_pa = 0 + DEGREE;
	// else if (data.start == 'W')
	// 	g_pa = PI - DEGREE;
    g_px = data.player.x * g_cube_size_x;
    g_py = data.player.y * g_cube_size_y;
    // g_px = 2 * g_cube_size_x;
    // g_py = 2 * g_cube_size_y;
    g_pdx = cos(g_pa);
    g_pdy = sin(g_pa);
    g_texture_we = mlx_load_png(data.we);
    g_texture_ea = mlx_load_png(data.ea);
    g_texture_so = mlx_load_png(data.so);
    g_texture_no = mlx_load_png(data.no);
    draw_3d(mlx);
    mlx_loop_hook(mlx, &hook, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
	data_free(&data);
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}
